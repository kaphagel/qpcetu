#!/usr/bin/env python3
"""
Fix header files that have #pragma once at the top but still have #endif at the bottom.
This script removes the trailing #endif // HEADER_NAME_H lines.
"""

import os
import re

# List of files that need fixing
files_to_fix = [
    "./src/mainwindow.h",
    "./src/ui/thememanager.h",
    "./src/ui/controllercardwidget.h",
    "./src/ui/hamburgermenu.h",
    "./src/ui/modernmainwindow.h",
    "./src/ui/themesettingswidget.h",
    "./src/ui/applestyle.h",
    "./src/ui/virtualkeyboard.h",
    "./src/datawidget.h",
    "./src/navigation/breadcrumbwidget.h",
    "./src/navigation/navigationmanager.h",
    "./src/events/industrialeventmanager.h",
    "./src/strategies/controllerstrategy.h",
    "./src/industrialcontroller.h",
    "./src/data/datarepository.h",
    "./src/udpservice.h",
    "./src/graphwidget.h",
    "./src/commands/command.h",
    "./src/statemachine/controllerstatemachine.h",
    "./src/plugins/controllerplugininterface.h",
    "./src/services/controllerxmlservice.h",
    "./src/udpresponsepage.h",
    "./src/pages/dashboardpage.h",
    "./src/pages/industrialdatapage.h",
    "./src/pages/webbrowserpage.h",
    "./src/pages/controlleroverview.h",
    "./src/pages/settingspage.h",
    "./src/pages/dragdroppage_simple.h",
    "./src/pages/simpledragdroppage.h",
    "./src/pages/overviewpage.h",
    "./src/pages/udpresponsepage.h",
    "./src/controllermanager.h"
]

def fix_header_file(filepath):
    """Remove trailing #endif // HEADER_NAME_H from files that have #pragma once"""
    try:
        with open(filepath, 'r') as f:
            content = f.read()
        
        # Check if file has #pragma once
        if '#pragma once' not in content:
            print(f"SKIP {filepath}: No #pragma once found")
            return False
        
        # Remove trailing #endif // HEADER_NAME_H lines
        # Match #endif with optional comment at the end of file
        pattern = r'\n\s*#endif\s*//\s*\w+_H\s*\n*$'
        new_content = re.sub(pattern, '\n', content)
        
        if content == new_content:
            print(f"SKIP {filepath}: Already fixed or no #endif found")
            return False
        
        # Write back
        with open(filepath, 'w') as f:
            f.write(new_content)
        
        print(f"FIXED {filepath}")
        return True
        
    except Exception as e:
        print(f"ERROR {filepath}: {e}")
        return False

def main():
    fixed_count = 0
    for filepath in files_to_fix:
        if fix_header_file(filepath):
            fixed_count += 1
    
    print(f"\n=== Summary: Fixed {fixed_count}/{len(files_to_fix)} files ===")

if __name__ == '__main__':
    main()
