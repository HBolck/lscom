#ifndef FILESERVICE_H
#define FILESERVICE_H
#include <QString>
#include <QVariant>
#include "Service/Strategy/strategyfactory.h"

namespace lscom_service
{
    class FileService
    {
    public:
        FileService(strategy_factory::StrategyFactory *strategyFactory);

        /**
         * @brief 导入文件内容缓存
         */
        QList<QString> importFileContentCache;
        /**
         * @brief 导入的文件路径缓存
         */
        QString importFilePathCache;

        /**
         * @brief 清空文件
         */
        void fileClear();

        /**
         * @brief 逐行发送文件
         * @param interval
         */
        void SendFileByLine(uint interval);

    private:
        strategy_factory::StrategyFactory *strategyFactory;
    };

}

#endif // FILESERVICE_H
