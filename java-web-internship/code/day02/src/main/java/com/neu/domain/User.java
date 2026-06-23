package com.neu.domain;

/**
 * 用户领域对象 (Domain Object)
 * 用于新增/更新操作 (id, name, address)
 *
 * 注意: typeAliases 包扫描后，别名默认为 user
 */
public class User {

    private Integer id;
    private String name;
    private String address;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
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
}
