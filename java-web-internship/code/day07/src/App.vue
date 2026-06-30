<script setup>
import { useAuthStore } from './stores/auth'
import { useRouter } from 'vue-router'

const auth = useAuthStore()
const router = useRouter()

const handleLogout = () => {
  auth.logout()
  router.push('/login')
}
</script>

<template>
  <div id="app-container">
    <!-- 顶部导航栏，登录后显示 -->
    <el-container v-if="auth.isLoggedIn">
      <el-header class="app-header">
        <div class="header-left">
          <h2>用户管理系统</h2>
        </div>
        <div class="header-right">
          <span class="welcome-text">欢迎，{{ auth.username }}</span>
          <el-button type="danger" size="small" @click="handleLogout">退出登录</el-button>
        </div>
      </el-header>
      <el-container>
        <!-- 侧边栏 -->
        <el-aside width="200px" class="app-aside">
          <el-menu
            :default-active="$route.path"
            router
            background-color="#304156"
            text-color="#bfcbd9"
            active-text-color="#409EFF"
          >
            <el-menu-item index="/main">
              <span>首页</span>
            </el-menu-item>
            <el-menu-item index="/users">
              <span>用户列表</span>
            </el-menu-item>
            <el-menu-item index="/about">
              <span>关于</span>
            </el-menu-item>
          </el-menu>
        </el-aside>
        <!-- 主内容区 -->
        <el-main class="app-main">
          <RouterView />
        </el-main>
      </el-container>
    </el-container>

    <!-- 未登录时直接显示登录页 -->
    <div v-else class="login-wrapper">
      <RouterView />
    </div>
  </div>
</template>

<style>
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

html, body, #app, #app-container {
  height: 100%;
  width: 100%;
}

.app-header {
  background-color: #2b579a;
  color: #fff;
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 0 20px;
  height: 60px;
}

.header-left h2 {
  font-size: 20px;
}

.header-right {
  display: flex;
  align-items: center;
  gap: 15px;
}

.welcome-text {
  font-size: 14px;
}

.app-aside {
  background-color: #304156;
  min-height: calc(100vh - 60px);
}

.app-main {
  background-color: #f0f2f5;
  padding: 20px;
}

.login-wrapper {
  height: 100%;
}
</style>
