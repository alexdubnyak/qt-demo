#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
🎨 QT Button Demo - Simple Presentation
Demonstration of precise colors from Figma in QT application
"""

import sys
import os
from PyQt5 import QtWidgets, QtCore, QtGui

def load_stylesheet(path):
    """Load QSS styles from file"""
    try:
        with open(path, 'r', encoding='utf-8') as file:
            return file.read()
    except Exception as e:
        print(f"Failed to load stylesheet {path}:", e)
        return ""

class ButtonDemoWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.current_theme = "light"
        self.setup_ui()
        self.load_theme()
        
    def setup_ui(self):
        """Create user interface"""
        self.setWindowTitle("🎨 QT Button Demo - Precise colors from Figma frames")
        self.setFixedSize(900, 700)
        
        # Central widget
        central_widget = QtWidgets.QWidget()
        self.setCentralWidget(central_widget)
        
        # Main layout
        main_layout = QtWidgets.QVBoxLayout(central_widget)
        main_layout.setSpacing(20)
        main_layout.setContentsMargins(30, 30, 30, 30)
        
        # Header and theme toggle
        header_layout = QtWidgets.QHBoxLayout()
        
        title_label = QtWidgets.QLabel("QT Button Demo - Precise colors from Figma")
        title_label.setObjectName("titleLabel")
        title_label.setAlignment(QtCore.Qt.AlignLeft)
        
        self.theme_button = QtWidgets.QPushButton("Dark theme")
        self.theme_button.setObjectName("themeButton")
        self.theme_button.clicked.connect(self.toggle_theme)
        
        header_layout.addWidget(title_label)
        header_layout.addStretch()
        header_layout.addWidget(self.theme_button)
        
        main_layout.addLayout(header_layout)
        
        # Main buttons group
        main_group = QtWidgets.QGroupBox("Button states")
        main_group_layout = QtWidgets.QVBoxLayout(main_group)
        
        # Row 1: Normal state
        row1_layout = QtWidgets.QHBoxLayout()
        normal_label = QtWidgets.QLabel("Normal:")
        normal_label.setFixedWidth(70)
        normal_label.setAlignment(QtCore.Qt.AlignRight | QtCore.Qt.AlignVCenter)
        row1_layout.addWidget(normal_label, 0, QtCore.Qt.AlignVCenter)
        
        normal_sm = QtWidgets.QPushButton("Small")
        normal_sm.setObjectName("smallButton")
        
        normal_md = QtWidgets.QPushButton("Medium") 
        normal_md.setObjectName("mediumButton")
        
        normal_lg = QtWidgets.QPushButton("Large")
        normal_lg.setObjectName("largeButton")
        
        row1_layout.addWidget(normal_sm)
        row1_layout.addWidget(normal_md)
        row1_layout.addWidget(normal_lg)
        row1_layout.addStretch()
        
        # Row 2: Hover state (emulation)
        row2_layout = QtWidgets.QHBoxLayout()
        hover_label = QtWidgets.QLabel("Hover:")
        hover_label.setFixedWidth(70)
        hover_label.setAlignment(QtCore.Qt.AlignRight | QtCore.Qt.AlignVCenter)
        row2_layout.addWidget(hover_label, 0, QtCore.Qt.AlignVCenter)
        
        hover_sm = QtWidgets.QPushButton("Small")
        hover_sm.setObjectName("smallHoverButton")
        
        hover_md = QtWidgets.QPushButton("Medium")
        hover_md.setObjectName("mediumHoverButton")
        
        hover_lg = QtWidgets.QPushButton("Large")
        hover_lg.setObjectName("largeHoverButton")
        
        row2_layout.addWidget(hover_sm)
        row2_layout.addWidget(hover_md)
        row2_layout.addWidget(hover_lg)
        row2_layout.addStretch()
        
        # Row 3: Pressed state (emulation)
        row3_layout = QtWidgets.QHBoxLayout()
        pressed_label = QtWidgets.QLabel("Pressed:")
        pressed_label.setFixedWidth(70)
        pressed_label.setAlignment(QtCore.Qt.AlignRight | QtCore.Qt.AlignVCenter)
        row3_layout.addWidget(pressed_label, 0, QtCore.Qt.AlignVCenter)
        
        pressed_sm = QtWidgets.QPushButton("Small")
        pressed_sm.setObjectName("smallPressedButton")
        
        pressed_md = QtWidgets.QPushButton("Medium")
        pressed_md.setObjectName("mediumPressedButton")
        
        pressed_lg = QtWidgets.QPushButton("Large")
        pressed_lg.setObjectName("largePressedButton")
        
        row3_layout.addWidget(pressed_sm)
        row3_layout.addWidget(pressed_md)
        row3_layout.addWidget(pressed_lg)
        row3_layout.addStretch()
        
        # Row 4: Disabled state
        row4_layout = QtWidgets.QHBoxLayout()
        disabled_label = QtWidgets.QLabel("Disabled:")
        disabled_label.setFixedWidth(70)
        disabled_label.setAlignment(QtCore.Qt.AlignRight | QtCore.Qt.AlignVCenter)
        row4_layout.addWidget(disabled_label, 0, QtCore.Qt.AlignVCenter)
        
        disabled_sm = QtWidgets.QPushButton("Small")
        disabled_sm.setObjectName("smallDisabledButton")
        disabled_sm.setEnabled(False)
        
        disabled_md = QtWidgets.QPushButton("Medium")
        disabled_md.setObjectName("mediumDisabledButton")
        disabled_md.setEnabled(False)
        
        disabled_lg = QtWidgets.QPushButton("Large")
        disabled_lg.setObjectName("largeDisabledButton")
        disabled_lg.setEnabled(False)
        
        row4_layout.addWidget(disabled_sm)
        row4_layout.addWidget(disabled_md)
        row4_layout.addWidget(disabled_lg)
        row4_layout.addStretch()
        
        main_group_layout.addLayout(row1_layout)
        main_group_layout.addLayout(row2_layout)
        main_group_layout.addLayout(row3_layout)
        main_group_layout.addLayout(row4_layout)
        
        main_layout.addWidget(main_group)
        
        
        main_layout.addStretch()
        
    def load_theme(self):
        """Load current theme"""
        if self.current_theme == "light":
            style = load_stylesheet("light_theme.qss")
            self.theme_button.setText("Dark theme")
        else:
            style = load_stylesheet("dark_theme.qss") 
            self.theme_button.setText("Light theme")
        
        if style:
            QtWidgets.QApplication.instance().setStyleSheet(style)
        else:
            print(f"Error loading {self.current_theme}_theme.qss")
    
    def toggle_theme(self):
        """Toggle theme"""
        self.current_theme = "dark" if self.current_theme == "light" else "light"
        self.load_theme()
    

def main():
    """Main function"""
    app = QtWidgets.QApplication(sys.argv)
    
    # Check for QSS files
    required_files = ["light_theme.qss", "dark_theme.qss"]
    missing_files = []
    
    for file in required_files:
        if not os.path.exists(file):
            missing_files.append(file)
    
    if missing_files:
        msg = QtWidgets.QMessageBox()
        msg.setIcon(QtWidgets.QMessageBox.Warning)
        msg.setWindowTitle("Missing files")
        msg.setText(f"QSS files not found: {', '.join(missing_files)}")
        msg.setInformativeText("Make sure files are in the same folder as the script.")
        msg.exec_()
        return
    
    # Create and show window
    window = ButtonDemoWindow()
    window.show()
    
    # Center window on screen
    screen = app.primaryScreen()
    screen_geometry = screen.availableGeometry()
    window_geometry = window.frameGeometry()
    center_point = screen_geometry.center()
    window_geometry.moveCenter(center_point)
    window.move(window_geometry.topLeft())
    
    print("🎨 QT Button Demo started!")
    print("📋 Use theme toggle button to compare colors")
    print("📋 All colors precisely match Figma design")
    
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()
