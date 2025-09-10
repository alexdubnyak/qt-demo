#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QScreen>
#include <QRect>
#include <QUiLoader>
#include <QVBoxLayout>

class UIViewer : public QWidget {
    Q_OBJECT
public:
    UIViewer(const QString& uiFile, QWidget *parent = nullptr) : QWidget(parent) {
        loadUI(uiFile);
        setupConnections();
        loadTheme();
    }

private slots:
    void toggleTheme() {
        currentTheme = (currentTheme == "light") ? "dark" : "light";
        loadTheme();
        
        // Обновляем текст кнопки переключения темы
        QPushButton* themeButton = findChild<QPushButton*>("themeToggle");
        if (themeButton) {
            QString text = (currentTheme == "light") ? "🌙 Темная тема" : "☀️ Светлая тема";
            themeButton->setText(text);
        }
    }

    void onButtonClicked() {
        QPushButton* button = qobject_cast<QPushButton*>(sender());
        if (button) {
            QLabel* statusLabel = findChild<QLabel*>("statusLabel");
            if (statusLabel) {
                statusLabel->setText(QString("Нажата кнопка: %1").arg(button->text()));
            }
            qDebug() << "Нажата кнопка:" << button->text();
        }
    }

private:
    QString currentTheme = "light";
    QWidget* loadedWidget = nullptr;

    void loadUI(const QString& uiFile) {
        QUiLoader loader;
        QFile file(uiFile);
        
        if (!file.open(QFile::ReadOnly)) {
            QMessageBox::critical(this, "Ошибка", 
                QString("Не удалось открыть UI файл: %1").arg(uiFile));
            return;
        }

        loadedWidget = loader.load(&file, this);
        file.close();

        if (!loadedWidget) {
            QMessageBox::critical(this, "Ошибка", 
                QString("Не удалось загрузить UI из файла: %1").arg(uiFile));
            return;
        }

        // Создаем layout для размещения загруженного виджета
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(loadedWidget);

        // Копируем свойства окна из загруженного виджета
        setWindowTitle(loadedWidget->windowTitle());
        setMinimumSize(loadedWidget->minimumSize());
        resize(loadedWidget->size());

        qDebug() << "✅ UI файл успешно загружен!";
    }

    void setupConnections() {
        if (!loadedWidget) return;

        // Подключаем кнопку переключения темы
        QPushButton* themeButton = loadedWidget->findChild<QPushButton*>("themeToggle");
        if (themeButton) {
            connect(themeButton, &QPushButton::clicked, this, &UIViewer::toggleTheme);
        }

        // Подключаем все остальные кнопки
        QList<QPushButton*> buttons = loadedWidget->findChildren<QPushButton*>();
        for (QPushButton* button : buttons) {
            if (button != themeButton) {
                connect(button, &QPushButton::clicked, this, &UIViewer::onButtonClicked);
            }
        }
    }

    void loadTheme() {
        QString fileName = QString("%1_theme.qss").arg(currentTheme);
        QFile file(fileName);
        
        if (file.open(QFile::ReadOnly)) {
            QString styleSheet = QString::fromLatin1(file.readAll());
            qApp->setStyleSheet(styleSheet);
            qDebug() << "🎨 Тема" << currentTheme << "загружена";
        } else {
            qDebug() << "⚠️ Не удалось загрузить тему" << fileName;
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Устанавливаем свойства приложения
    app.setApplicationName("UI Viewer");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Demo Company");

    QString uiFile = "demo.ui";
    
    // Проверяем существование UI файла
    if (!QFile::exists(uiFile)) {
        QMessageBox::critical(nullptr, "Ошибка", 
            QString("UI файл не найден: %1\n\nУбедитесь, что файл находится в текущей директории").arg(uiFile));
        return 1;
    }

    // Проверяем файлы стилей
    QStringList styleFiles = {"light_theme.qss", "dark_theme.qss"};
    QStringList missingFiles;
    
    for (const QString& file : styleFiles) {
        if (!QFile::exists(file)) {
            missingFiles << file;
        }
    }
    
    if (!missingFiles.isEmpty()) {
        QMessageBox::warning(nullptr, "Предупреждение", 
            QString("Не найдены файлы стилей: %1\n\nПриложение будет работать без стилей").arg(missingFiles.join(", ")));
    }

    // Создаем и показываем окно
    UIViewer viewer(uiFile);
    viewer.show();

    // Центрируем окно на экране
    QScreen* screen = app.primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    QRect windowGeometry = viewer.frameGeometry();
    QPoint centerPoint = screenGeometry.center();
    windowGeometry.moveCenter(centerPoint);
    viewer.move(windowGeometry.topLeft());

    qDebug() << "🚀 UI Viewer запущен!";
    qDebug() << "💡 Используйте кнопку переключения темы для смены стилей";

    return app.exec();
}

#include "ui_viewer.moc"
