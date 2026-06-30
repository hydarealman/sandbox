<script>
export default {
  name: 'MainView',
  data() {
    return {
      currentTime: '',
      stats: {
        totalUsers: 6,
        activeUsers: 4,
        newUsersToday: 2,
        departments: 5,
      },
    }
  },
  mounted() {
    this.updateTime()
    this.timer = setInterval(() => {
      this.updateTime()
    }, 1000)
  },
  beforeUnmount() {
    if (this.timer) {
      clearInterval(this.timer)
    }
  },
  methods: {
    updateTime() {
      const now = new Date()
      this.currentTime = now.toLocaleString('zh-CN')
    },
  },
}
</script>

<template>
  <div class="main-container">
    <el-row :gutter="20" class="welcome-row">
      <el-col :span="24">
        <el-card class="welcome-card">
          <h2>欢迎来到用户管理系统</h2>
          <p class="current-time">当前时间：{{ currentTime }}</p>
        </el-card>
      </el-col>
    </el-row>

    <!-- 统计卡片 -->
    <el-row :gutter="20" class="stats-row">
      <el-col :span="6">
        <el-card class="stat-card" shadow="hover">
          <div class="stat-content">
            <div class="stat-icon" style="background-color: #409EFF;">
              <span>👥</span>
            </div>
            <div class="stat-info">
              <p class="stat-number">{{ stats.totalUsers }}</p>
              <p class="stat-label">用户总数</p>
            </div>
          </div>
        </el-card>
      </el-col>
      <el-col :span="6">
        <el-card class="stat-card" shadow="hover">
          <div class="stat-content">
            <div class="stat-icon" style="background-color: #67C23A;">
              <span>✅</span>
            </div>
            <div class="stat-info">
              <p class="stat-number">{{ stats.activeUsers }}</p>
              <p class="stat-label">活跃用户</p>
            </div>
          </div>
        </el-card>
      </el-col>
      <el-col :span="6">
        <el-card class="stat-card" shadow="hover">
          <div class="stat-content">
            <div class="stat-icon" style="background-color: #E6A23C;">
              <span>🆕</span>
            </div>
            <div class="stat-info">
              <p class="stat-number">{{ stats.newUsersToday }}</p>
              <p class="stat-label">今日新增</p>
            </div>
          </div>
        </el-card>
      </el-col>
      <el-col :span="6">
        <el-card class="stat-card" shadow="hover">
          <div class="stat-content">
            <div class="stat-icon" style="background-color: #F56C6C;">
              <span>🏢</span>
            </div>
            <div class="stat-info">
              <p class="stat-number">{{ stats.departments }}</p>
              <p class="stat-label">部门数量</p>
            </div>
          </div>
        </el-card>
      </el-col>
    </el-row>

    <!-- 快捷入口 -->
    <el-row :gutter="20" class="quick-row">
      <el-col :span="24">
        <el-card class="quick-card">
          <template #header>
            <span>快捷操作</span>
          </template>
          <el-row :gutter="15">
            <el-col :span="8">
              <el-button type="primary" class="quick-btn" @click="$router.push('/users')">
                用户列表管理
              </el-button>
            </el-col>
            <el-col :span="8">
              <el-button type="success" class="quick-btn" @click="$router.push('/users')">
                添加新用户
              </el-button>
            </el-col>
            <el-col :span="8">
              <el-button type="info" class="quick-btn" @click="$router.push('/about')">
                查看关于
              </el-button>
            </el-col>
          </el-row>
        </el-card>
      </el-col>
    </el-row>

    <!-- 系统信息 -->
    <el-row :gutter="20" class="info-row">
      <el-col :span="12">
        <el-card class="info-card">
          <template #header>
            <span>系统信息</span>
          </template>
          <el-descriptions :column="1" border size="small">
            <el-descriptions-item label="系统名称">用户管理系统</el-descriptions-item>
            <el-descriptions-item label="前端框架">Vue 3 + Element Plus</el-descriptions-item>
            <el-descriptions-item label="路由管理">Vue Router 4</el-descriptions-item>
            <el-descriptions-item label="状态管理">Pinia</el-descriptions-item>
          </el-descriptions>
        </el-card>
      </el-col>
      <el-col :span="12">
        <el-card class="info-card">
          <template #header>
            <span>操作日志</span>
          </template>
          <el-timeline>
            <el-timeline-item timestamp="2026-06-30 09:00" placement="top">
              系统启动正常
            </el-timeline-item>
            <el-timeline-item timestamp="2026-06-30 09:15" placement="top">
              用户 admin 登录系统
            </el-timeline-item>
            <el-timeline-item timestamp="2026-06-30 10:30" placement="top">
              新增用户数据
            </el-timeline-item>
            <el-timeline-item timestamp="2026-06-30 14:00" placement="top">
              系统运行稳定
            </el-timeline-item>
          </el-timeline>
        </el-card>
      </el-col>
    </el-row>
  </div>
</template>

<style scoped>
.main-container {
  max-width: 1200px;
  margin: 0 auto;
}

.welcome-row {
  margin-bottom: 20px;
}

.welcome-card h2 {
  font-size: 22px;
  color: #303133;
  margin-bottom: 8px;
}

.current-time {
  font-size: 14px;
  color: #909399;
}

.stats-row {
  margin-bottom: 20px;
}

.stat-card {
  cursor: pointer;
}

.stat-content {
  display: flex;
  align-items: center;
  gap: 15px;
}

.stat-icon {
  width: 60px;
  height: 60px;
  border-radius: 8px;
  display: flex;
  align-items: center;
  justify-content: center;
}

.stat-icon span {
  font-size: 28px;
}

.stat-number {
  font-size: 28px;
  font-weight: bold;
  color: #303133;
}

.stat-label {
  font-size: 13px;
  color: #909399;
  margin-top: 4px;
}

.quick-row {
  margin-bottom: 20px;
}

.quick-btn {
  width: 100%;
  height: 60px;
  font-size: 15px;
}

.info-row {
  margin-bottom: 20px;
}

.info-card {
  min-height: 250px;
}
</style>
