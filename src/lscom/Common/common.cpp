#include "Common/common.h"

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
