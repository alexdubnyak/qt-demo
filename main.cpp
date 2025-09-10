#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QGroupBox>
#include <QFile>
#include <QDir>
#include <QDebug>

class ThemeManager : public QObject {
    Q_OBJECT
public:
    enum Theme {
        Light,
        Dark
    };

    static ThemeManager* instance() {
        static ThemeManager instance;
        return &instance;
    }

    void setTheme(Theme theme) {
        currentTheme = theme;
        loadStyleSheet();
        emit themeChanged();
    }

    Theme getCurrentTheme() const {
        return currentTheme;
    }

signals:
    void themeChanged();

private:
    ThemeManager() : currentTheme(Light) {}
    Theme currentTheme;

    void loadStyleSheet() {
        QFile file(currentTheme == Light ? ":/styles/light_theme.qss" : ":/styles/dark_theme.qss");
        if (file.open(QFile::ReadOnly)) {
            QString styleSheet = QString::fromLatin1(file.readAll());
            qApp->setStyleSheet(styleSheet);
        } else {
            // Fallback to local files if resources are not available
            QString fileName = currentTheme == Light ? "light_theme.qss" : "dark_theme.qss";
            QFile localFile(fileName);
            if (localFile.open(QFile::ReadOnly)) {
                QString styleSheet = QString::fromLatin1(localFile.readAll());
                qApp->setStyleSheet(styleSheet);
            } else {
                qDebug() << "Could not load stylesheet:" << fileName;
            }
        }
    }
};

class ButtonDemoWidget : public QWidget {
    Q_OBJECT
public:
    ButtonDemoWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
        connectSignals();
    }

private slots:
    void toggleTheme() {
        auto* themeManager = ThemeManager::instance();
        ThemeManager::Theme newTheme = (themeManager->getCurrentTheme() == ThemeManager::Light) 
                                     ? ThemeManager::Dark 
                                     : ThemeManager::Light;
        themeManager->setTheme(newTheme);
        
        themeToggle->setText(newTheme == ThemeManager::Light ? "🌙 Темная тема" : "☀️ Светлая тема");
    }

    void onButtonClicked() {
        QPushButton* button = qobject_cast<QPushButton*>(sender());
        if (button) {
            statusLabel->setText(QString("Нажата кнопка: %1").arg(button->text()));
        }
    }

private:
    void setupUI() {
        setWindowTitle("QT Button Demo - Демонстрация кнопок");
        setMinimumSize(800, 600);

        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        // Header with theme toggle
        QHBoxLayout* headerLayout = new QHBoxLayout();
        QLabel* titleLabel = new QLabel("Демонстрация стилей кнопок QT");
        titleLabel->setObjectName("titleLabel");
        
        themeToggle = new QPushButton("🌙 Темная тема");
        themeToggle->setObjectName("themeToggle");
        
        headerLayout->addWidget(titleLabel);
        headerLayout->addStretch();
        headerLayout->addWidget(themeToggle);
        
        mainLayout->addLayout(headerLayout);

        // Primary buttons section
        QGroupBox* primaryGroup = new QGroupBox("Основные кнопки");
        QHBoxLayout* primaryLayout = new QHBoxLayout(primaryGroup);
        
        QPushButton* primaryBtn = new QPushButton("Основная");
        primaryBtn->setObjectName("primaryButton");
        
        QPushButton* secondaryBtn = new QPushButton("Вторичная");
        secondaryBtn->setObjectName("secondaryButton");
        
        QPushButton* successBtn = new QPushButton("Успех");
        successBtn->setObjectName("successButton");
        
        QPushButton* warningBtn = new QPushButton("Предупреждение");
        warningBtn->setObjectName("warningButton");
        
        QPushButton* dangerBtn = new QPushButton("Опасность");
        dangerBtn->setObjectName("dangerButton");
        
        primaryLayout->addWidget(primaryBtn);
        primaryLayout->addWidget(secondaryBtn);
        primaryLayout->addWidget(successBtn);
        primaryLayout->addWidget(warningBtn);
        primaryLayout->addWidget(dangerBtn);
        
        mainLayout->addWidget(primaryGroup);

        // Size variants section
        QGroupBox* sizeGroup = new QGroupBox("Размеры кнопок");
        QHBoxLayout* sizeLayout = new QHBoxLayout(sizeGroup);
        
        QPushButton* smallBtn = new QPushButton("Маленькая");
        smallBtn->setObjectName("smallButton");
        
        QPushButton* mediumBtn = new QPushButton("Средняя");
        mediumBtn->setObjectName("mediumButton");
        
        QPushButton* largeBtn = new QPushButton("Большая");
        largeBtn->setObjectName("largeButton");
        
        sizeLayout->addWidget(smallBtn);
        sizeLayout->addWidget(mediumBtn);
        sizeLayout->addWidget(largeBtn);
        sizeLayout->addStretch();
        
        mainLayout->addWidget(sizeGroup);

        // State variants section
        QGroupBox* stateGroup = new QGroupBox("Состояния кнопок");
        QHBoxLayout* stateLayout = new QHBoxLayout(stateGroup);
        
        QPushButton* normalBtn = new QPushButton("Обычная");
        normalBtn->setObjectName("normalButton");
        
        QPushButton* hoverBtn = new QPushButton("Наведение");
        hoverBtn->setObjectName("hoverButton");
        
        QPushButton* pressedBtn = new QPushButton("Нажатая");
        pressedBtn->setObjectName("pressedButton");
        
        QPushButton* disabledBtn = new QPushButton("Отключена");
        disabledBtn->setObjectName("disabledButton");
        disabledBtn->setEnabled(false);
        
        stateLayout->addWidget(normalBtn);
        stateLayout->addWidget(hoverBtn);
        stateLayout->addWidget(pressedBtn);
        stateLayout->addWidget(disabledBtn);
        stateLayout->addStretch();
        
        mainLayout->addWidget(stateGroup);

        // Icon buttons section
        QGroupBox* iconGroup = new QGroupBox("Кнопки с иконками");
        QHBoxLayout* iconLayout = new QHBoxLayout(iconGroup);
        
        QPushButton* iconBtn1 = new QPushButton("📁 Открыть");
        iconBtn1->setObjectName("iconButton");
        
        QPushButton* iconBtn2 = new QPushButton("💾 Сохранить");
        iconBtn2->setObjectName("iconButton");
        
        QPushButton* iconBtn3 = new QPushButton("🗑️ Удалить");
        iconBtn3->setObjectName("iconButtonDanger");
        
        iconLayout->addWidget(iconBtn1);
        iconLayout->addWidget(iconBtn2);
        iconLayout->addWidget(iconBtn3);
        iconLayout->addStretch();
        
        mainLayout->addWidget(iconGroup);

        // Outline buttons section
        QGroupBox* outlineGroup = new QGroupBox("Контурные кнопки");
        QHBoxLayout* outlineLayout = new QHBoxLayout(outlineGroup);
        
        QPushButton* outlineBtn1 = new QPushButton("Контурная");
        outlineBtn1->setObjectName("outlineButton");
        
        QPushButton* outlineBtn2 = new QPushButton("Контурная успех");
        outlineBtn2->setObjectName("outlineSuccessButton");
        
        QPushButton* outlineBtn3 = new QPushButton("Контурная опасность");
        outlineBtn3->setObjectName("outlineDangerButton");
        
        outlineLayout->addWidget(outlineBtn1);
        outlineLayout->addWidget(outlineBtn2);
        outlineLayout->addWidget(outlineBtn3);
        outlineLayout->addStretch();
        
        mainLayout->addWidget(outlineGroup);

        // Status label
        statusLabel = new QLabel("Готово к демонстрации");
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignCenter);
        
        mainLayout->addWidget(statusLabel);
        mainLayout->addStretch();

        // Connect all buttons to the slot
        connectButtonSignals(this);
    }

    void connectButtonSignals(QWidget* parent) {
        QList<QPushButton*> buttons = parent->findChildren<QPushButton*>();
        for (QPushButton* button : buttons) {
            if (button != themeToggle) {
                connect(button, &QPushButton::clicked, this, &ButtonDemoWidget::onButtonClicked);
            }
        }
    }

    void connectSignals() {
        connect(themeToggle, &QPushButton::clicked, this, &ButtonDemoWidget::toggleTheme);
        connect(ThemeManager::instance(), &ThemeManager::themeChanged, this, [this]() {
            statusLabel->setText("Тема изменена!");
        });
    }

    QPushButton* themeToggle;
    QLabel* statusLabel;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("QT Button Demo");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Demo Company");

    // Initialize theme
    ThemeManager::instance()->setTheme(ThemeManager::Light);

    ButtonDemoWidget window;
    window.show();

    return app.exec();
}

#include "main.moc"

