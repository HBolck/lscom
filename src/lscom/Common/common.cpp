#include "Common/common.h"
#include "common.h"

/**
 * @brief 判断 QString 是否可以转成 uint，并获取转换后的结果
 * @param str 待判断和转换的 QString
 * @param value 用于存储转换结果的 uint 指针
 * @return 转换是否成功
 */
bool isQStringToUint(const QString &str, uint *value)
{
    bool ok;
    *value = str.toUInt(&ok);
    if (!ok)
        *value = 0;
    return ok;
}

/**
 * @brief 获取QString格式的HEX字符串内容
 * @param data
 */
QString getQStringHex(QByteArray data)
{
    QString hexString;
    for (char byte : data)
    {
        hexString.append(QString("%1 ").arg(static_cast<quint8>(byte), 2, 16, QChar('0').toUpper()));
    }
    return hexString;
}

void setNumOnLabel(QLabel *lel, QString str, long num)
{
    lel->setText(str + QString::number(num));
}

QString mapToJson(const QMap<QString, QString> &map)
{
    QJsonObject jsonObject;
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        jsonObject[it.key()] = it.value();
    }
    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc.toJson(QJsonDocument::Compact);
}

QString configToJson(const Config &config)
{
    QJsonObject jsonConfig;
    QJsonObject jsonParam;
    jsonParam["SendAreaData"] = config.InputParam.SendAreaData;
    jsonParam["RevDataToFilePath"] = config.InputParam.RevDataToFilePath;
    jsonParam["SendInterval"] = config.InputParam.SendInterval;
    jsonParam["ImportFilePath"] = config.InputParam.ImportFilePath;
    jsonParam["IsPLineSend"] = config.InputParam.IsPLineSend;
    jsonParam["IsFileLoopSend"] = config.InputParam.IsFileLoopSend;
    jsonParam["FileSendLineInterval"] = config.InputParam.FileSendLineInterval;
    QJsonArray dataList;
    for (const QString &str : config.InputParam.SendDataList)
    {
        dataList.append(str);
    }
    jsonParam["SendDataList"] = dataList;
    jsonConfig["InputParam"] = jsonParam;
    QJsonDocument jsonDoc(jsonConfig);
    return jsonDoc.toJson(QJsonDocument::Compact);
}

void writeJsonToFile(const QString &fileName, const QString &json)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << json;
        file.close();
    }
}

bool checkFileExist(const QString &fileName)
{
    if (fileName.isNull())
        return false;
    if (fileName.isEmpty())
        return false;

    QFile file(fileName);
    return file.exists();
}

bool createFolderIfNotExist(const QString &folderPath)
{
    QDir dir(folderPath);
    if (!dir.exists())
    {
        if (dir.mkpath(folderPath))
        {
            return true;
        }
        else
        {
            qDebug() << "创建文件加失败";
            return false;
        }
    }
    return true;
}
/**
 * @brief 读取文件到QString
 * @param fileName
 * @return
 */
QString readFileContents(const QString &fileName)
{
    if (fileName.isNull())
        return "";
    if (fileName.isEmpty())
        return "";
    if (checkFileExist(fileName) == false)
        return "";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QString();
    }

    QTextStream in(&file);
    QString contents = in.readAll();
    file.close();

    return contents;
}

/**
 * @brief readFileContentList
 * @param fileName
 * @return
 */
QList<QString> readFileContentList(const QString &fileName)
{
    QList<QString> list;
    if (fileName.isNull())
        return list;
    if (fileName.isEmpty())
        return list;
    if (checkFileExist(fileName) == false)
        return list;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return list;
    }
    QTextStream in(&file);
    QString temp = "";
    while ((temp = in.readLine()).isNull() == false)
    {
        list.append(temp);
    }
    file.close();
    return list;
}

bool jsonToConfig(const QString &jsonStr, Config &config)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());
    if (!jsonDoc.isObject())
    {
        return false;
    }

    QJsonObject jsonObj = jsonDoc.object();
    if (!jsonObj.contains("InputParam"))
    {
        return false;
    }

    QJsonObject inputParamObj = jsonObj.value("InputParam").toObject();
    config.InputParam.RevDataToFilePath = inputParamObj.value("RevDataToFilePath").toString();
    config.InputParam.SendAreaData = inputParamObj.value("SendAreaData").toString();
    config.InputParam.SendInterval = inputParamObj.value("SendInterval").toString();
    config.InputParam.ImportFilePath = inputParamObj.value("ImportFilePath").toString();
    config.InputParam.IsPLineSend = inputParamObj.value("IsPLineSend").toString();
    config.InputParam.IsFileLoopSend = inputParamObj.value("IsFileLoopSend").toString();
    config.InputParam.FileSendLineInterval = inputParamObj.value("FileSendLineInterval").toString();
    QList<QString> list;
    if (inputParamObj.contains("SendDataList") && inputParamObj.value("SendDataList").isArray())
    {
        QJsonArray array = inputParamObj.value("SendDataList").toArray();
        for (const auto &value : array)
        {
            list.append(value.toString());
        }
        config.InputParam.SendDataList = list;
    }
    return true;
}

bool stringIsNllOrEmpty(const QString &str)
{
    return str.isEmpty() || str.isNull();
}
