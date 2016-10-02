; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "DatvExpressServerApp"
#define MyAppVersion "1.4"
#define MyAppPublisher "DATV-Express LLC"
#define MyAppURL "http://www.datv-express.com/"
#define MyAppExeName "DatvExpressServerApp.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{669572C4-63BC-4CE4-A415-26DE7E164159}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName=C:\DatvExpress\{#MyAppName}
DefaultGroupName=DatvExpress
InfoAfterFile=C:\Users\Charles\Documents\Visual Studio 2012\Projects\DatvExpressServerApp\Release\README.TXT
OutputBaseFilename=setup_datvexpress
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\Users\Charles\Documents\Visual Studio 2012\Projects\DatvExpressServerApp\Release\DatvExpressServerApp.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Charles\Documents\Visual Studio 2012\Projects\DatvExpressServerApp\Release\datvexpress8.ihx"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Charles\Documents\Visual Studio 2012\Projects\DatvExpressServerApp\Release\datvexpressdvbs.rbf"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Charles\Documents\Visual Studio 2012\Projects\DatvExpressServerApp\Release\datvexpress.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Charles\Documents\Visual Studio 2012\Projects\DatvExpressServerApp\Release\README.TXT"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Charles\Documents\Visual Studio 2012\Projects\DatvExpressServerApp\Release\MajorUdpSend.ax"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Charles\Documents\Visual Studio 2012\Projects\DatvExpressServerApp\Release\filter.bat"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\filter.bat"; Parameters: "{app}"; WorkingDir: "{app}"; Flags: nowait postinstall runascurrentuser
Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"; Flags: nowait postinstall skipifsilent unchecked; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"