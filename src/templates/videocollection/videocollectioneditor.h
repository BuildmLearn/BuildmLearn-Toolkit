/*
  Copyright (c) 2015, BuildmLearn Contributors listed at http://buildmlearn.org/people/
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

#ifndef VIDEOCOLLECTIONEDITOR_H
#define VIDEOCOLLECTIONEDITOR_H

#include "core/templateeditor.h"

#include "ui_videocollectioneditor.h"
#include "templates/videocollection/videocollectionvideo.h"


namespace Ui {
  class VideoCollectionEditor;
}

/// \brief Editor for Video collection.
/// \ingroup template-videocollection
class VideoCollectionEditor : public TemplateEditor {
    Q_OBJECT

    friend class VideoCollectionSimulator;
    friend class VideoCollectionCore;

  public:
    explicit VideoCollectionEditor(TemplateCore *core, QWidget *parent = 0);
    virtual ~VideoCollectionEditor();

    bool canGenerateApplications();
    QString generateBundleData();
    bool loadBundleData(const QString &bundle_data);

    QList<VideoCollectionVideo> activeVideos() const;

    QString projectName();
    QString authorName();

  private:
    void checkAuthor();
    void checkTitle();
    void checkUrl();
    void urlChanged();
    void checkName();

  private slots:
    void setEditorsEnabled(bool enabled);
    void updateVideoCount();
    void addVideo();
    void loadVideo(int index);
    void saveVideo();
    void removeVideo();
    void loadThumbnail(const QString &thumbnail_path);
    void onUrlChanged(const QString &new_url);
    void onTitleChanged(const QString &new_title);
    void onAuthorChanged(const QString &new_author);
    void onNameChanged(const QString &new_name);
    void configureUpDown();
    void moveVideoUp();
    void moveVideoDown();
    void addVideo(const QString& url, const QString& title, const QString& description, const QString& thumbnail_path);
    //void downloadingError(int error_code);
    //void sourceDownloaded();

  private:
    Ui::VideoCollectionEditor *m_ui;
    VideoCollectionVideo m_activeVideo;
};

#endif // VIDEOCOLLECTIONEDITOR_H
