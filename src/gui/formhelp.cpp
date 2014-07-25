/*
  Copyright (c) 2012, BuildmLearn Contributors listed at http://buildmlearn.org/people/
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the name of the BuildmLearn nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "gui/formhelp.h"

#include "miscellaneous/iconfactory.h"

#include <QShowEvent>


FormHelp::FormHelp(bool do_not_show_again_enabled, QWidget *parent)
  : QDialog(parent),
    m_ui(new Ui::FormHelp),
    m_displayNeverShowCheckbox(do_not_show_again_enabled) {
  m_ui->setupUi(this);

  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  setWindowIcon(IconFactory::instance()->fromTheme("application-help"));

  //: About toolkit dialog title.
  setWindowTitle(tr("Help"));

  // Establish connections.
  connect(this, SIGNAL(accepted()), this, SLOT(onAccepted()));

  //: Help HTML contents, translate including HTML markup!!!
  QString help_contents = tr("<body>"
                             "<h2 style=\"text-align: center\">Welcome to help</h2>"
                             ""
                             "<p style=\"text-align: center\">"
                             "<a href=\"#introduction\">Introduction</a> | "
                             "<a href=\"#simulator\">Simulator</a> | "
                             "<a href=\"#xml-bundles\">XML bundles</a> | "
                             "<a href=\"#other-facts\">Other facts</a>"
                             "</p>"
                             ""
                             "<a name=\"introduction\"></a><h3 style=\"text-align: center\">Introduction</h3>"
                             "<p>"
                             "BuildmLearn Toolkit is an application which helps you to create interactive mobile applications in a WYSIWYG way. You do not need to know anything about programming, no extra skills are required. You simply put in the content you would like to have in your application and that's all."
                             "</p>"
                             ""
                             "<p>"
                             "You can start new mobile application project by going into main menu and using item \"Project -> New project\". Toolkit contains several templates to start with, including template for quiz-like applications or template for learning of word spelling. After creating new project, you will see that main window of BuildmLearn Toolkit contains user interface which expects your input, this is the \"editor\" of your project. When you save your project using \"Project -> Save project as...\" menu item, then all data from \"editor\" are saved, so that you can continue in your work later."
                             "</p>"
                             ""
                             "<p>"
                             "BuildmLearn Toolkit's main ability is that it is able to generate mobile applications for Android (*.apk files) for you. You just need to select template, fill it with data and use menu item \"Project -> Generate mobile application\". Note that this option is only available if \"editor\" of your template contains enough data and application has correct settings. You can tweak relevant settings in \"Tools -> Settings\" dialog, in \"Project .apk file generation\" section. You need to have JRE (Java Runtime Environment) installed in order for this feature to work."
                             "</p>"
                             ""
                             "<a name=\"simulator\"></a><h3 style=\"text-align: center\">Simulator</h3>"
                             "<p>"
                             "This applications provides you with option to test you application before you generate it. Simply load your project, fill it with data and hit \"Simulator -> Run new simulation\" menu item. Separate simulator window with your simulation will appear if not visible already."
                             "</p>"
                             ""
                             "<a name=\"xml-bundles\"></a><h3 style=\"text-align: center\">XML bundles</h3>"
                             "<p>"
                             "You can save your work so that you can carry it to another computer and/or continue in your work later. You can do that by pushing \"Project -> Save project as...\" menu item. Projects are stored in special XML files with \"*.buildmlearn\" suffix."
                             "</p>"
                             ""
                             "<a name=\"other-facts\"></a><h3 style=\"text-align: center\">Other facts</h3>"
                             "<p>"
                             "BuildmLearn Toolkit is portable application which does not store anything to system registry. The only system folders it uses are user-specific folders."
                             "</p>"
                             "</body>");

  m_ui->m_txtHelp->setText(help_contents);
}

FormHelp::~FormHelp() {
  delete m_ui;
}

void FormHelp::showEvent(QShowEvent *e) {
  QDialog::showEvent(e);

  if (!e->spontaneous()) {
    m_ui->m_cmbDoNotShowAgain->setEnabled(m_displayNeverShowCheckbox);
  }
}

void FormHelp::onAccepted() {
  if (m_ui->m_cmbDoNotShowAgain->isEnabled()) {
    qApp->settings()->setValue(APP_CFG_GUI,
                               "show_help_startup",
                               !m_ui->m_cmbDoNotShowAgain->isChecked());
  }
}
