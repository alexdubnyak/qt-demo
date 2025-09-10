#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Простой просмотрщик UI файлов Qt без Designer
"""

import sys
import os
from PyQt5 import QtWidgets, uic

def load_stylesheet(path):
    """Загрузить QSS стили из файла"""
    try:
        with open(path, 'r', encoding='utf-8') as file:
            return file.read()
    except Exception as e:
        print(f"Не удалось загрузить стили {path}:", e)
        return ""

class UIViewer(QtWidgets.QMainWindow):
    def __init__(self, ui_file):
        super().__init__()
        self.current_theme = "light"
        
        # Загружаем UI файл прямо в self (поскольку demo.ui создает QMainWindow)
        try:
            uic.loadUi(ui_file, self)
            print(f"✅ UI файл {ui_file} успешно загружен!")
        except Exception as e:
            print(f"❌ Ошибка загрузки UI файла {ui_file}: {e}")
            sys.exit(1)
        
        self.setup_connections()
        self.load_theme()
        
    def setup_connections(self):
        """Настройка соединений сигналов"""
        # Подключаем кнопку переключения темы
        if hasattr(self, 'themeButton'):
            self.themeButton.clicked.connect(self.toggle_theme)
        
        # Подключаем все остальные кнопки к общему обработчику
        buttons = self.findChildren(QtWidgets.QPushButton)
        for button in buttons:
            if button != getattr(self, 'themeButton', None):
                button.clicked.connect(lambda checked, btn=button: self.on_button_clicked(btn))
    
    def toggle_theme(self):
        """Переключение темы"""
        self.current_theme = "dark" if self.current_theme == "light" else "light"
        self.load_theme()
        
        # Обновляем текст кнопки
        if hasattr(self, 'themeButton'):
            if self.current_theme == "light":
                self.themeButton.setText("Dark theme")
            else:
                self.themeButton.setText("Light theme")
    
    def load_theme(self):
        """Загрузка текущей темы"""
        theme_file = f"{self.current_theme}_theme.qss"
        style = load_stylesheet(theme_file)
        
        if style:
            QtWidgets.QApplication.instance().setStyleSheet(style)
            print(f"🎨 Тема {self.current_theme} загружена")
        else:
            print(f"⚠️ Не удалось загрузить тему {theme_file}")
    
    def on_button_clicked(self, button):
        """Обработчик нажатия кнопок"""
        print(f"🔘 Нажата кнопка: {button.text()}")

def main():
    """Главная функция"""
    app = QtWidgets.QApplication(sys.argv)
    
    # Проверяем наличие UI файла
    ui_file = "demo.ui"
    if not os.path.exists(ui_file):
        print(f"❌ UI файл {ui_file} не найден!")
        print("📍 Убедитесь, что файл находится в текущей директории")
        return
    
    # Проверяем наличие файлов стилей
    required_files = ["light_theme.qss", "dark_theme.qss"]
    missing_files = [f for f in required_files if not os.path.exists(f)]
    
    if missing_files:
        print(f"⚠️ Не найдены файлы стилей: {', '.join(missing_files)}")
        print("🎨 Приложение будет работать без стилей")
    
    # Создаем и показываем окно
    try:
        viewer = UIViewer(ui_file)
        viewer.show()
        
        # Центрируем окно на экране
        screen = app.primaryScreen()
        screen_geometry = screen.availableGeometry()
        window_geometry = viewer.frameGeometry()
        center_point = screen_geometry.center()
        window_geometry.moveCenter(center_point)
        viewer.move(window_geometry.topLeft())
        
        print("🚀 UI Viewer запущен!")
        print("💡 Используйте кнопку переключения темы для смены стилей")
        
        sys.exit(app.exec_())
        
    except Exception as e:
        print(f"❌ Ошибка запуска приложения: {e}")
        return

if __name__ == "__main__":
    main()
