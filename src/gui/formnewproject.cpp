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

#include "gui/formnewproject.h"

#include "core/templateentrypoint.h"
#include "core/templatefactory.h"
#include "miscellaneous/iconfactory.h"

#include <QShowEvent>


FormNewProject::FormNewProject(TemplateFactory *template_manager, QWidget *parent)
  : QDialog(parent),
    m_ui(new Ui::FormNewProject), m_adjusted(false) {
  m_ui->setupUi(this);

  m_ui->m_lblThumbnail->setFixedSize(300, 213);
  m_ui->m_listTemplates->setFixedWidth(200);
  m_ui->m_lblDescription->setFixedWidth(300);

  QMargins description_margins = m_ui->m_lblDescription->contentsMargins();

  description_margins.setTop(20);

  m_ui->m_lblDescription->setContentsMargins(description_margins);

  connect(m_ui->m_listTemplates, SIGNAL(currentRowChanged(int)), this, SLOT(templateSelected(int)));
  connect(m_ui->m_listTemplates, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(accept()));

  // This window mustn't be deleted when closed by user.
  setAttribute(Qt::WA_DeleteOnClose, false);
  setWindowIcon(IconFactory::instance()->fromTheme("project-new"));
  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog | (windowFlags() & ~Qt::WindowContextHelpButtonHint));

  loadTemplates(template_manager->availableTemplates());
}

FormNewProject::~FormNewProject() {
  delete m_ui;
}

TemplateEntryPoint *FormNewProject::startNewTemplate() {
  if (exec() == QDialog::Accepted && m_ui->m_listTemplates->currentRow() >= 0) {
    return static_cast<TemplateEntryPoint*>(m_ui->m_listTemplates->currentItem()->data(Qt::UserRole).value<void*>());
  }
  else {
    return NULL;
  }
}

void FormNewProject::showEvent(QShowEvent *e) {
  if (!m_adjusted) {
    adjustSize();
    adjustPosition(parentWidget());

    m_adjusted = true;
  }

  e->accept();
}

void FormNewProject::templateSelected(int index) {
  if (index >= 0) {
    TemplateEntryPoint *entry_point = static_cast<TemplateEntryPoint*>(m_ui->m_listTemplates->currentItem()->data(Qt::UserRole).value<void*>());

    m_ui->m_lblDescription->setText(entry_point->description());
    m_ui->m_lblThumbnail->setPixmap(QPixmap(APP_TEMPLATES_PATH + QDir::separator() +
                                            entry_point->baseFolder() + QDir::separator() +
                                            entry_point->thumbnailImage()));
  }
}

void FormNewProject::loadTemplates(const QList<TemplateEntryPoint*> &entry_points) {
  foreach (TemplateEntryPoint *entry_point, entry_points) {
    // Add the template.
    (new QListWidgetItem(entry_point->humanName(),
                         m_ui->m_listTemplates))->setData(Qt::UserRole,
                                                          QVariant::fromValue((void*) entry_point));
  }

  if (m_ui->m_listTemplates->count() > 0) {
    m_ui->m_listTemplates->setCurrentRow(0);
  }
}
