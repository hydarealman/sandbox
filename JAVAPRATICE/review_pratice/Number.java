package review_pratice;

import java.io.Serializable;

/**
 * 数值类型的抽象基类，提供各基本数值类型之间的转换方法。
 */
public abstract class Number implements Serializable {
    // 抽象方法
    public abstract int intValue();
    public abstract long longValue();
    public abstract float floatValue();
    public abstract double doubleValue();
    
    // Java 8 新增
    public byte byteValue() {
        return (byte)intValue();
    }
    public short shortValue() {
        return (short)intValue();
    }
}
