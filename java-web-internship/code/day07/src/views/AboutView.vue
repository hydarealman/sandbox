<script>
export default {
  name: 'AboutView',
  data() {
    return {
      version: '1.0.0',
    }
  },
}
</script>

<template>
  <div class="about-container">
    <el-card class="about-card">
      <template #header>
        <h2>关于本项目</h2>
      </template>
      <el-descriptions :column="1" border>
        <el-descriptions-item label="项目名称">PC前端项目 - 用户管理系统</el-descriptions-item>
        <el-descriptions-item label="版本号">{{ version }}</el-descriptions-item>
        <el-descriptions-item label="前端框架">Vue 3（Options API）</el-descriptions-item>
        <el-descriptions-item label="UI 组件库">Element Plus</el-descriptions-item>
        <el-descriptions-item label="路由管理">Vue Router 4</el-descriptions-item>
        <el-descriptions-item label="状态管理">Pinia</el-descriptions-item>
        <el-descriptions-item label="构建工具">Vite</el-descriptions-item>
        <el-descriptions-item label="开发日期">2026-06-30</el-descriptions-item>
      </el-descriptions>

      <el-divider />

      <h3>功能模块</h3>
      <el-row :gutter="15" style="margin-top: 15px;">
        <el-col :span="8">
          <el-card shadow="hover" class="module-card">
            <h4>🔐 登录界面</h4>
            <p>用户登录认证，表单验证</p>
          </el-card>
        </el-col>
        <el-col :span="8">
          <el-card shadow="hover" class="module-card">
            <h4>🏠 主界面</h4>
            <p>系统仪表盘，数据统计展示</p>
          </el-card>
        </el-col>
        <el-col :span="8">
          <el-card shadow="hover" class="module-card">
            <h4>👥 用户列表界面</h4>
            <p>用户增删改查，搜索分页</p>
          </el-card>
        </el-col>
      </el-row>
    </el-card>
  </div>
</template>

<style scoped>
.about-container {
  max-width: 900px;
  margin: 0 auto;
}

.about-card h2 {
  margin: 0;
  font-size: 20px;
}

.module-card {
  text-align: center;
  min-height: 120px;
}

.module-card h4 {
  font-size: 16px;
  margin-bottom: 8px;
}

.module-card p {
  font-size: 13px;
  color: #909399;
}
</style>
