import { defineStore } from 'pinia'
import { ref } from 'vue'

export const useUserStore = defineStore('user', () => {
  // 模拟用户数据
  const users = ref([
    { id: 1, name: '张三', age: 25, email: 'zhangsan@qq.com', phone: '13800001111', department: '技术部' },
    { id: 2, name: '李四', age: 30, email: 'lisi@qq.com', phone: '13800002222', department: '产品部' },
    { id: 3, name: '王五', age: 28, email: 'wangwu@qq.com', phone: '13800003333', department: '设计部' },
    { id: 4, name: '赵六', age: 32, email: 'zhaoliu@qq.com', phone: '13800004444', department: '市场部' },
    { id: 5, name: '孙七', age: 26, email: 'sunqi@qq.com', phone: '13800005555', department: '技术部' },
    { id: 6, name: '周八', age: 29, email: 'zhouba@qq.com', phone: '13800006666', department: '财务部' },
  ])

  let nextId = 7

  const getUserList = () => {
    return users.value
  }

  const addUser = (user) => {
    user.id = nextId++
    users.value.push(user)
  }

  const updateUser = (updatedUser) => {
    const index = users.value.findIndex(u => u.id === updatedUser.id)
    if (index !== -1) {
      users.value[index] = { ...updatedUser }
    }
  }

  const deleteUser = (id) => {
    users.value = users.value.filter(u => u.id !== id)
  }

  const searchUsers = (keyword) => {
    if (!keyword) return users.value
    const kw = keyword.toLowerCase()
    return users.value.filter(u =>
      u.name.includes(kw) ||
      u.email.includes(kw) ||
      u.department.includes(kw)
    )
  }

  return { users, getUserList, addUser, updateUser, deleteUser, searchUsers }
})
