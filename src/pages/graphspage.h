#pragma once
#include <QWidget>
#include <QVBoxLayout>

class GraphWidget;
class GraphViewModel;
class ModbusService;
class ThemeManager;

/**
 * @brief Graphs page - Pure UI for data visualization
 * 
 * This page displays real-time graphs of industrial data (EEG, shield harmonics, etc.).
 * All business logic has been moved to GraphViewModel following MVVM pattern.
 * 
 * Pattern: MVVM - View layer (RULE-200)
 * Location: src/pages/ (will be moved to src/views/pages/ in Phase 5)
 * 
 * Responsibilities:
 * - UI layout and styling ONLY
 * - Connect to ViewModel signals
 * - Update UI based on ViewModel data
 * - NO business logic (RULE-100)
 */
class GraphsPage : public QWidget {
    Q_OBJECT
    
public:
    explicit GraphsPage(QWidget* parent = nullptr);
    ~GraphsPage() override;

private slots:
    void onEegDataUpdated(double value);
    void onErrorOccurred(const QString& error);
    void onConnectionStateChanged(bool connected);

private:
    void setupUI();
    void connectSignals();
    void applyTheme();
    
    // ViewModel (business logic)
    GraphViewModel* m_viewModel;
    ModbusService* m_modbusService;
    
    // UI Components
    GraphWidget* m_eegGraph;
    GraphWidget* m_graph2;
    GraphWidget* m_graph3;
    GraphWidget* m_graph4;
    QVBoxLayout* m_mainLayout;
    
    // Services
    ThemeManager* m_themeManager;
};
