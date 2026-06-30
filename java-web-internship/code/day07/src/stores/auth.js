import { defineStore } from 'pinia'
import { ref, computed } from 'vue'

export const useAuthStore = defineStore('auth', () => {
  const username = ref(localStorage.getItem('username') || '')
  const isLoggedIn = ref(!!localStorage.getItem('isLoggedIn'))

  const login = (user, pwd) => {
    // 模拟登录验证：admin/123456 或任意用户名密码长度>=3
    if (user.length >= 3 && pwd.length >= 3) {
      username.value = user
      isLoggedIn.value = true
      localStorage.setItem('isLoggedIn', 'true')
      localStorage.setItem('username', user)
      return { success: true, message: '登录成功' }
    }
    return { success: false, message: '用户名和密码长度至少3位' }
  }

  const logout = () => {
    username.value = ''
    isLoggedIn.value = false
    localStorage.removeItem('isLoggedIn')
    localStorage.removeItem('username')
  }

  return { username, isLoggedIn, login, logout }
})
