package com.neu.vo;

/**
 * 用户值对象 (Value Object)
 * 对应 user 表的查询结果 (id, name, address)
 *
 * 注意: typeAliases 包扫描后，别名默认为 userVO (类名首字母小写)
 */
public class UserVO {

    private int id;
    private String name;
    private String address;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    @Override
    public String toString() {
        return "UserVO{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", address='" + address + '\'' +
                '}';
    }
}
