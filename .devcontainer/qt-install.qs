function Controller() {
    installer.autoRejectMessageBoxes();
    installer.installationFinished.connect(function() {
        gui.clickButton(buttons.NextButton);
    });
}

Controller.prototype.IntroductionPageCallback = function() {
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.TargetDirectoryPageCallback = function() {
    gui.currentPageWidget().TargetDirectoryLineEdit.setText("/opt/Qt");
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.ComponentSelectionPageCallback = function() {
    // Install Qt 6.6.4 GCC 64-bit with QuickControls2 and other modules
    var widget = gui.currentPageWidget();
    widget.deselectAll();
    widget.selectComponent("qt.qt6.666.gcc_64"); // Qt base + modules
    widget.selectComponent("qt.qt6.666.qtquickcontrols2.gcc_64"); // QuickControls2
    widget.selectComponent("qt.qt6.666.qtdeclarative.gcc_64"); // QML/Declarative
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.LicenseAgreementPageCallback = function() {
    gui.clickButton(buttons.AcceptLicenseButton);
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.ReadyForInstallationPageCallback = function() {
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.PerformInstallationPageCallback = function() {
    installer.performInstallation();
}

Controller.prototype.FinishedPageCallback = function() {
    gui.clickButton(buttons.FinishButton);
}
