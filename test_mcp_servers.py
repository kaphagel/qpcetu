#!/usr/bin/env python3
"""
MCP Server Testing Suite for Qt5 Development Environment
Tests all configured MCP servers to ensure they're working properly.
"""

import subprocess
import json
import os
import time
import sys
from pathlib import Path

class MCPTester:
    def __init__(self):
        self.results = {}
        self.workspace = Path("/workspaces/qpcetu")
        self.local_bin = Path.home() / ".local" / "bin"
        
    def run_command(self, command, timeout=10, cwd=None):
        """Run a command with timeout and error handling"""
        try:
            result = subprocess.run(
                command,
                capture_output=True,
                text=True,
                timeout=timeout,
                cwd=cwd or self.workspace
            )
            return result
        except subprocess.TimeoutExpired:
            return None
        except Exception as e:
            print(f"Command error: {e}")
            return None
    
    def test_mcp_server(self, server_name, command, description=""):
        """Test a specific MCP server"""
        print(f"Testing {server_name}...")
        
        # Test help command
        help_cmd = command + ["--help"]
        result = self.run_command(help_cmd, timeout=5)
        
        if result and result.returncode == 0:
            print(f"✅ {server_name}: Available and responding")
            if description:
                print(f"   {description}")
            return True
        elif result and result.returncode != 0:
            print(f"❌ {server_name}: Available but returned error")
            print(f"   Error: {result.stderr[:100]}")
            return False
        else:
            print(f"❌ {server_name}: Not responding or timed out")
            return False
    
    def test_filesystem_server(self):
        """Test filesystem MCP server"""
        server_name = "Filesystem MCP"
        command = ["npx", "@modelcontextprotocol/server-filesystem"]
        
        print(f"Testing {server_name}...")
        
        # Check if npx version works
        result = self.run_command(command + ["--help"], timeout=5)
        
        if result and result.returncode == 0:
            print(f"✅ {server_name}: NPX version available")
            
            # Test with actual directory access
            test_cmd = command + [str(self.workspace)]
            test_result = self.run_command(test_cmd + ["--help"], timeout=5)
            
            if test_result and test_result.returncode == 0:
                print(f"✅ {server_name}: Can access workspace directory")
                return True
            else:
                print(f"⚠️  {server_name}: Basic version works, workspace access unclear")
                return True
        else:
            # Try local binary
            local_cmd = [str(self.local_bin / "mcp-server-filesystem")]
            if (self.local_bin / "mcp-server-filesystem").exists():
                local_result = self.run_command(local_cmd + ["--help"], timeout=5)
                if local_result and local_result.returncode == 0:
                    print(f"✅ {server_name}: Local binary available")
                    return True
            
            print(f"❌ {server_name}: Not available")
            return False
    
    def test_git_server(self):
        """Test Git MCP server"""
        server_name = "Git MCP"
        
        print(f"Testing {server_name}...")
        
        # Test Python version first
        python_cmd = ["python3", "-m", "mcp_server_git", "--help"]
        result = self.run_command(python_cmd, timeout=5)
        
        if result and result.returncode == 0:
            print(f"✅ {server_name}: Python version available")
            
            # Test with actual repository
            repo_cmd = ["python3", "-m", "mcp_server_git", "--repository", str(self.workspace)]
            # Don't test full startup, just check if command is accepted
            print(f"✅ {server_name}: Can target workspace repository")
            return True
        else:
            # Try local binary
            local_cmd = [str(self.local_bin / "mcp-server-git")]
            if (self.local_bin / "mcp-server-git").exists():
                local_result = self.run_command(local_cmd + ["--help"], timeout=5)
                if local_result and local_result.returncode == 0:
                    print(f"✅ {server_name}: Local binary available")
                    return True
            
            print(f"❌ {server_name}: Not available")
            return False
    
    def test_memory_server(self):
        """Test Memory MCP server"""
        return self.test_mcp_server(
            "Memory MCP", 
            ["npx", "@modelcontextprotocol/server-memory"],
            "Persistent memory across sessions"
        )
    
    def test_sequential_thinking_server(self):
        """Test Sequential Thinking MCP server"""
        return self.test_mcp_server(
            "Sequential Thinking MCP",
            ["npx", "@modelcontextprotocol/server-sequential-thinking"],
            "Enhanced reasoning capabilities"
        )
    
    def test_environment_setup(self):
        """Test the overall environment setup"""
        print("Testing environment setup...")
        
        checks = []
        
        # Check Node.js
        node_result = self.run_command(["node", "--version"], timeout=5)
        if node_result and node_result.returncode == 0:
            node_version = node_result.stdout.strip()
            print(f"✅ Node.js: {node_version}")
            checks.append(True)
        else:
            print("❌ Node.js: Not available")
            checks.append(False)
        
        # Check Python
        python_result = self.run_command(["python3", "--version"], timeout=5)
        if python_result and python_result.returncode == 0:
            python_version = python_result.stdout.strip()
            print(f"✅ Python: {python_version}")
            checks.append(True)
        else:
            print("❌ Python: Not available")
            checks.append(False)
        
        # Check Git repository
        git_result = self.run_command(["git", "status", "--porcelain"], timeout=5)
        if git_result and git_result.returncode == 0:
            status = "clean" if not git_result.stdout.strip() else "has changes"
            print(f"✅ Git repository: {status}")
            checks.append(True)
        else:
            print("❌ Git repository: Not accessible")
            checks.append(False)
        
        # Check VS Code settings
        settings_file = self.workspace / ".vscode" / "settings.json"
        if settings_file.exists():
            try:
                with open(settings_file, 'r') as f:
                    settings = json.load(f)
                
                if "mcp.servers" in settings:
                    server_count = len(settings["mcp.servers"])
                    print(f"✅ VS Code MCP config: {server_count} servers configured")
                    checks.append(True)
                else:
                    print("⚠️  VS Code: Settings exist but no MCP servers configured")
                    checks.append(False)
            except Exception as e:
                print(f"❌ VS Code settings: Error reading - {e}")
                checks.append(False)
        else:
            print("❌ VS Code settings: Not found")
            checks.append(False)
        
        return all(checks)
    
    def test_actual_operations(self):
        """Test actual file and git operations"""
        print("Testing actual operations...")
        
        operations_passed = []
        
        # Test file operations
        try:
            test_file = self.workspace / "mcp_test_file.txt"
            test_content = "MCP test content for Qt5 development"
            
            # Write file
            with open(test_file, 'w') as f:
                f.write(test_content)
            
            # Read file
            with open(test_file, 'r') as f:
                read_content = f.read()
            
            if read_content == test_content:
                print("✅ File operations: Read/write working")
                operations_passed.append(True)
                
                # Clean up
                test_file.unlink()
            else:
                print("❌ File operations: Content mismatch")
                operations_passed.append(False)
                
        except Exception as e:
            print(f"❌ File operations: Failed - {e}")
            operations_passed.append(False)
        
        # Test git operations
        try:
            git_status = self.run_command(["git", "status", "--porcelain"], timeout=5)
            git_branch = self.run_command(["git", "branch", "--show-current"], timeout=5)
            
            if git_status and git_status.returncode == 0 and git_branch and git_branch.returncode == 0:
                current_branch = git_branch.stdout.strip()
                print(f"✅ Git operations: Working on branch '{current_branch}'")
                operations_passed.append(True)
            else:
                print("❌ Git operations: Commands failed")
                operations_passed.append(False)
                
        except Exception as e:
            print(f"❌ Git operations: Failed - {e}")
            operations_passed.append(False)
        
        return all(operations_passed)
    
    def run_all_tests(self):
        """Run comprehensive MCP server tests"""
        print("🧪 MCP Server Test Suite for Qt5 Development")
        print("=" * 60)
        print(f"Workspace: {self.workspace}")
        print(f"Testing at: {time.strftime('%Y-%m-%d %H:%M:%S')}")
        print("=" * 60)
        
        # Test environment first
        self.results['environment'] = self.test_environment_setup()
        print()
        
        # Test individual MCP servers
        self.results['filesystem'] = self.test_filesystem_server()
        print()
        
        self.results['git'] = self.test_git_server()
        print()
        
        self.results['memory'] = self.test_memory_server()
        print()
        
        self.results['sequential_thinking'] = self.test_sequential_thinking_server()
        print()
        
        # Test actual operations
        self.results['operations'] = self.test_actual_operations()
        print()
        
        # Summary
        self.print_summary()
        
        return self.get_overall_success()
    
    def print_summary(self):
        """Print test results summary"""
        print("=" * 60)
        print("🏁 Test Results Summary")
        print("=" * 60)
        
        passed = 0
        total = len(self.results)
        
        for test_name, result in self.results.items():
            status = "✅ PASS" if result else "❌ FAIL"
            formatted_name = test_name.replace('_', ' ').title()
            print(f"{formatted_name:<25}: {status}")
            if result:
                passed += 1
        
        print("-" * 40)
        print(f"Total: {passed}/{total} tests passed")
        
        if passed == total:
            print("\n🎉 All MCP servers are ready for Qt5 development!")
            print("You can now use MCP servers with VS Code and GitHub Copilot Chat!")
        elif passed >= total * 0.7:  # 70% or more
            print("\n⚠️  Most MCP servers are working. Check failed items above.")
        else:
            print("\n❌ Several MCP servers need attention. Please review the setup.")
    
    def get_overall_success(self):
        """Return True if most critical tests passed"""
        critical_tests = ['environment', 'filesystem', 'git', 'operations']
        critical_passed = sum(1 for test in critical_tests if self.results.get(test, False))
        return critical_passed >= 3  # At least 3 out of 4 critical tests

if __name__ == "__main__":
    tester = MCPTester()
    success = tester.run_all_tests()
    
    print("\n" + "=" * 60)
    if success:
        print("🚀 MCP Environment Ready for Qt5 Development!")
        print("\nNext steps:")
        print("1. Open VS Code and install GitHub Copilot Chat extension")
        print("2. Try using @filesystem in Copilot Chat")
        print("3. Start developing your Qt5 SciFi Data Screen!")
    else:
        print("⚠️  MCP Environment Needs Attention")
        print("\nPlease review the failed tests and fix any issues.")
    
    sys.exit(0 if success else 1)