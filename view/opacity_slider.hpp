#pragma once

#include <QSlider>

namespace holebridge {
namespace todolist {

class OpacitySlider : public QSlider {
public:
    OpacitySlider(QWidget* parent = nullptr) {
        // 设置透明度极限值
        this->setRange(0, 100);
        this->setValue(100);

        this->setTracking(true);

        // 设置方向
        this->setOrientation(Qt::Horizontal);

        // 设置样式表
        this->setStyleSheet(R"(
            QSlider::groove:horizontal {
                border: 0px;
                background: #1E90FF;
                height: 4px;
                border-radius: 2px;
                padding-left: 0px;
                padding-right: 0px;
            }
            QSlider::sub-page:horizontal {
                background: #1E90FF;
                border: 2px;
                height: 4px;
                border-radius: 2px;
            }
            QSlider::add-page:horizontal {
                background: #EAEAEA;
                border: 0px;
                height: 3px;
                border-radius: 2px;
            }
            QSlider::handle:horizontal 
            {
                background: #1E90FF;
                width: 13px;
                margin-top: -5px;
                margin-bottom: -5px;
                border-radius: 6px;
            }

            QSlider::handle:horizontal:hover {
                background: #1E90FF;
                border: 3px solid white;
                width: 7px;
                margin-top: -5px;
                margin-bottom: -5px;
                border-radius: 5.5px;
            }
        )");
    }
};

}
}