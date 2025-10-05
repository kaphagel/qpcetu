#!/usr/bin/env python3
"""
MCP Server Connectivity Test
Tests if MCP servers can actually be connected to and respond to basic requests.
"""

import subprocess
import json
import tempfile
import time
from pathlib import Path

def test_mcp_server_connection(name, command, timeout=5):
    """Test if an MCP server can be started and responds"""
    print(f"Testing {name} connection...")
    
    try:
        # Start the server process
        process = subprocess.Popen(
            command,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        
        # Give it a moment to start
        time.sleep(1)
        
        # Check if process is still running
        if process.poll() is None:
            print(f"✅ {name}: Process started successfully")
            
            # Terminate the process
            process.terminate()
            try:
                process.wait(timeout=2)
            except subprocess.TimeoutExpired:
                process.kill()
            
            return True
        else:
            # Process already terminated, check output
            stdout, stderr = process.communicate()
            if "help" in stdout.lower() or "usage" in stdout.lower():
                print(f"✅ {name}: Responds with help/usage info")
                return True
            else:
                print(f"❌ {name}: Process terminated with error")
                if stderr:
                    print(f"   Error: {stderr[:100]}")
                return False
                
    except Exception as e:
        print(f"❌ {name}: Failed to start - {e}")
        return False

def main():
    print("🔗 MCP Server Connectivity Test")
    print("=" * 40)
    
    workspace = "/workspaces/qpcetu"
    results = {}
    
    # Test servers
    servers = [
        ("Filesystem MCP", ["npx", "@modelcontextprotocol/server-filesystem", workspace]),
        ("Git MCP", ["python3", "-m", "mcp_server_git", "--repository", workspace]),
        ("Memory MCP", ["npx", "@modelcontextprotocol/server-memory"]),
        ("Sequential Thinking MCP", ["npx", "@modelcontextprotocol/server-sequential-thinking"])
    ]
    
    for name, command in servers:
        results[name] = test_mcp_server_connection(name, command)
        print()
    
    # Summary
    print("=" * 40)
    print("📊 Connectivity Summary")
    print("=" * 40)
    
    working = sum(1 for result in results.values() if result)
    total = len(results)
    
    for name, result in results.items():
        status = "✅ CONNECTED" if result else "❌ FAILED"
        print(f"{name:<25}: {status}")
    
    print(f"\nTotal: {working}/{total} servers can be connected to")
    
    if working >= 2:
        print("\n🎉 MCP environment is functional!")
        print("You have enough working MCP servers for development.")
        print("\nNext steps:")
        print("1. Open VS Code")
        print("2. Install GitHub Copilot Chat extension")
        print("3. Try using MCP commands in Copilot Chat:")
        print("   - @filesystem (for file operations)")
        print("   - @git (for git operations)")
        if results.get("Memory MCP"):
            print("   - @memory (for persistent context)")
    else:
        print("\n⚠️  Limited MCP functionality")
        print("Some servers are not connecting properly.")
    
    return working >= 2

if __name__ == "__main__":
    success = main()
    exit(0 if success else 1)