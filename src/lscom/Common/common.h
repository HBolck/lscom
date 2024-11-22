#ifndef COMMON_H
#define COMMON_H

#endif // COMMON_H
#include <QCoreApplication>
//公共定义的区域
struct name
{
    name() {}
};

/**
 * @brief 判断 QString 是否可以转成 uint，并获取转换后的结果
 * @param str 待判断和转换的 QString
 * @param value 用于存储转换结果的 uint 指针
 * @return 转换是否成功
 */
bool isQStringToUint(const QString &str,uint *value);


/**
 * @brief 获取QString格式的HEX字符串内容
 * @param data
 */
QString getQStringHex(QByteArray data);
