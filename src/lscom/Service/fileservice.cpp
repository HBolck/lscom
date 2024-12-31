#include "fileservice.h"

namespace lscom_service
{

    lscom_service::FileService::FileService(strategy_factory::StrategyFactory *strategyFactory)
    {
        this->strategyFactory = strategyFactory;
    }

    void lscom_service::FileService::fileClear()
    {
        this->importFileContentCache.clear();
        this->importFilePathCache.clear();
    }

    void lscom_service::FileService::SendFileByLine(uint interval)
    {
        QElapsedTimer timer;
        for (const QString &data : this->importFileContentCache)
        {
            timer.restart();
            while (timer.elapsed() < interval)
            {
                QCoreApplication::processEvents(); // 用于处理当前线程中的待处理事件 保证主线程不阻塞
            }
            this->strategyFactory->PotocolImp->SendData(data.toUtf8());

            // 这个操作是异步的 这里不适合
            //  QTimer::singleShot(interval, this, [=]()
            //                     { this->serviceAdapter->serialService->SendData(data.toUtf8()); });
        }
    }   
}
