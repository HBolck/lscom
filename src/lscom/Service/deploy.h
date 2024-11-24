#ifndef DEPLOY_H
#define DEPLOY_H

#include <QObject>
#include "lscom.h"

namespace lscom_service
{
    class deploy :  public QObject
    {
        Q_OBJECT
    public:
        deploy();
        deploy(Ui::lscom *lscom);
        ~deploy();

    private:
        Ui::lscom *lscom;
    };

}

#endif // DEPLOY_H
