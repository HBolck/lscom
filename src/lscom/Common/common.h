#ifndef COMMON_H
#define COMMON_H

#include <QCoreApplication>
#include <QLabel>

#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QJsonArray>
#include <QFileDialog>

// 默认标题
#define GLOBAL_TITLE "lscom串口工具"
// 默认配置文件名称
#define GLOBAL_CONFIG_FILE_NAME "lscom.json"
// 源码地址
#define GLOBAL_CODE_SOURCE_URL "https://gitee.com/hblockd/lscom"
#define GLOBAL_IMPORT_FILE_EXT "Text Files (*.txt)"

/**
 * @brief 输入参数的数据
 */
struct InputParam
{
    /**
     * @brief 发送区域的数据
     */
    QString SendAreaData;
    /**
     * @brief 接收数据到文件的路径
     */
    QString RevDataToFilePath;

    /**
     * @brief 定时发送频率
     */
    QString SendInterval;

    /**
     * @brief 发送数据的集合
     */
    QList<QString> SendDataList;

    /**
     * @brief 导入的文件路径
     */
    QString ImportFilePath;

    /**
     * @brief 文件循环发送使能
     */
    QString IsFileLoopSend;

    /**
     * @brief 文件逐行发送使能
     */
    QString IsPLineSend;

    /**
     * @brief 文件发送行间隔
     */
    QString FileSendLineInterval;


};

/**
 * @brief 配置数据
 */
struct Config
{
    InputParam InputParam;
};

/**
 * @brief The TimeFormat enum
 */
enum TimeFormat
{
    YYMMDDHHmmss,
    YYMMDDHH,
    YYMMDD
};

/**
 * @brief 判断 QString 是否可以转成 uint，并获取转换后的结果
 * @param str 待判断和转换的 QString
 * @param value 用于存储转换结果的 uint 指针
 * @return 转换是否成功
 */
bool
isQStringToUint(const QString &str, uint *value);

/**
 * @brief 获取QString格式的HEX字符串内容
 * @param data
 */
QString getQStringHex(QByteArray data);

/**
 * @brief 给标签设置数值
 * @param lel
 * @param str
 * @param num
 */
void setNumOnLabel(QLabel *lel, QString str, long num);

/**
 * @brief varinatToJson
 * @param variant
 * @return
 */
QString mapToJson(const QMap<QString, QString> &map);

/**
 * @brief 配置信息转成json
 * @param config
 * @return
 */
QString configToJson(const Config &config);

/**
 * @brief 将json写入文件
 * @param fileName
 * @param json
 */
void writeJsonToFile(const QString &fileName, const QString &json);

/**
 * @brief jsonToConfig
 * @param jsonStr
 * @param config
 * @return
 */
bool jsonToConfig(const QString &jsonStr, Config &config);

/**
 * @brief 读取文件到QString
 * @param fileName
 * @return
 */
QString readFileContents(const QString &fileName);

/**
 * @brief 读取文件到列表
 */
QList<QString> readFileContentList(const QString &fileName);

/**
 * @brief 检查文件是否存在
 * @param fileName
 * @return
 */
bool checkFileExist(const QString &fileName);

/**
 * @brief 检查文件目录 如果不存在就创建
 * @param folderPath
 * @return
 */
bool createFolderIfNotExist(const QString &folderPath);

bool stringIsNllOrEmpty(const QString &str);

#endif // COMMON_H
