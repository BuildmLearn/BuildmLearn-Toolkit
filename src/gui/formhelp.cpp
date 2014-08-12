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
                             "<a href=\"#getting-started\">Getting started</a> | "
                             "<a href=\"#saved-projects\">Working with saved projects</a> | "
                             "<a href=\"#simulator\">Simulator</a> | "
                             "<a href=\"#mobile-applications\">Generating mobile applications</a> | "
                             "<a href=\"#upload-store\">Submitting mobile applications to BuildmLearn Store</a> | "
                             "<a href=\"#settings\">Settings and other facts</a>"
                             "</p>"
                             ""
                             "<a name=\"introduction\"></a><h3 style=\"text-align: center\">Introduction</h3>"
                             "<p>"
                             "BuildmLearn Toolkit is an application which helps you to create interactive mobile applications in a WYSIWYG way. You do not need to know anything about programming, no extra skills are required."
                             "</p>"
                             "<p>"
                             "The toolkit comes with a number of useful mobile application templates that you can choose from. Each template can be customised with your learning material (be it from textbook chapters or other sources) to create m-Learning applications."
                             "</p>"
                             "<p>"
                             "Each mobile application template that comes with the toolkit is designed for specific purposes, however you are free to use the templates as they suit your learning material."
                             "</p>"
                             ""
                             "<a name=\"getting-started\"></a><h3 style=\"text-align: center\">Getting started</h3>"
                             "<p>"
                             "You can start a new mobile application project by going into main menu and selecting \"Project -> New project\". The toolkit contains several templates to start with, including template for quiz-like applications or template for learning of word spellings. Please choose the one that suits your learning material the most."
                             "</p>"
                             "<p>"
                             "After creating a new project, you will see that main window of BuildmLearn Toolkit contains user interface which expects your input, this is the \"editor\" of your project. Please add your custom learning material into the editor, you will find options for adding as much content as you wish. There are also fields where you should input the name of your mobile application and your name (i.e. the name of the author)."
                             "</p>"
                             "<a name=\"saved-projects\"></a><h3 style=\"text-align: center\">Working with saved projects</h3>"
                             "<p>"
                             "You can save your work so that you can carry it to another computer and/or continue in your work later. You can do this by selecting \"Project -> Save project as...\". Projects are stored in files \"*.buildmlearn\" extension."
                             "</p>"
                             "<p>"
                             "If you wish to work with a previously saved project, go to \"Project -> Load project\" and select your saved project file to load it. You may continue to work on this project and generate mobile applications as well."
                             "</p>"
                             ""
                             "<a name=\"simulator\"></a><h3 style=\"text-align: center\">Simulator</h3>"
                             "<p>"
                             "Toolkit comes with a mobile phone simulator, using which you may test your mobile application and adjust your content before you finalize it. "
                             "</p>"
                             "<p>"
                             "When you have added some custom content into the editor, go to Simulator menu and choose \"Run new simulation\". A simulator window will show up and you will then be able to test your mobile applications on the simulator. You may stop the simulator when you are done with testing the application and continue to add content to the editor or generate your mobile applications."
                             "</p>"
                             ""
                             "<a name=\"mobile-applications\"></a><h3 style=\"text-align: center\">Generating mobile applications</h3>"
                             "<p>"
                             "After you have added your learning material to the toolkit and have tested it on the simulator, it is time to generate your mobile application. By generating mobile applications you then have the ability to share this application with other people (your students, other teachers, etc.)."
                             "</p>"
                             "<p>"
                             "To generate your mobile application, go to \"Project -> Generate mobile application\". Note that this option would only be available when you have added your learning material to the template. Choosing this option would create an application installer file for you to distribute. You may share this file with your students so that they can install the applications on their mobile phones or tablet devices."
                             "</p>"
                             "<p>"
                             "Note: You need to have JRE (Java Runtime Environment) installed in order for this feature to work."
                             "</p>"
                             ""
                             "<a name=\"upload-store\"></a><h3 style=\"text-align: center\">Submitting mobile applications to BuildmLearn Store</h3>"
                             "<p>"
                             "BuildmLearn Store is a collection of m-Learning applications which is available on Google Play store. Anyone can download the store to access the applications in the BuildmLearn store. Basically, choosing to submit your applications to the BuildmLearn store may facilitate an easy distribution to your target audience and also many other store users who may benefit from your learning material."
                             "</p>"
                             "<p>"
                             "You have an option to submit your mobile applications to the BuildmLearn store. To do this choose \"Project -> Submit application to store\". You will be asked to fill some basic information about the application before submitting."
                             "</p>"
                             "<p>"
                             "Once you have submitted your mobile application to the store, it would go through a quick review before it appears on the BuildmLearn store. You will get an email notification when the application is available on the BuildmLearn store, so please provide a valid email address while submitting."
                             "</p>"
                             ""
                             "<a name=\"settings\"></a><h3 style=\"text-align: center\">Settings and other facts</h3>"
                             "<p>"
                             "BuildmLearn Toolkit has many options that can be tweaked in 'Tools -> settings'. The settings provided are self explanatory. The toolkit is a portable application which does not store anything to system registry. The only system folders it uses are user-specific folders."
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
