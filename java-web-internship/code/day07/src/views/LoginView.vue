<script>
import { useAuthStore } from '@/stores/auth'

export default {
  name: 'LoginView',
  data() {
    return {
      loginForm: {
        username: '',
        password: '',
      },
      loginRules: {
        username: [
          { required: true, message: '请输入用户名', trigger: 'blur' },
          { min: 3, message: '用户名至少3个字符', trigger: 'blur' },
        ],
        password: [
          { required: true, message: '请输入密码', trigger: 'blur' },
          { min: 3, message: '密码至少3个字符', trigger: 'blur' },
        ],
      },
      loading: false,
    }
  },
  methods: {
    handleLogin() {
      this.$refs.loginFormRef.validate((valid) => {
        if (valid) {
          this.loading = true
          const auth = useAuthStore()
          // 模拟登录请求延迟
          setTimeout(() => {
            const result = auth.login(this.loginForm.username, this.loginForm.password)
            if (result.success) {
              this.$message.success(result.message)
              this.$router.push('/main')
            } else {
              this.$message.error(result.message)
            }
            this.loading = false
          }, 800)
        }
      })
    },
    handleReset() {
      this.$refs.loginFormRef.resetFields()
    },
  },
}
</script>

<template>
  <div class="login-container">
    <div class="login-card">
      <h1 class="login-title">用户管理系统</h1>
      <p class="login-subtitle">PC前端项目 - 登录</p>

      <el-form
        ref="loginFormRef"
        :model="loginForm"
        :rules="loginRules"
        label-width="0"
        size="large"
        class="login-form"
      >
        <el-form-item prop="username">
          <el-input
            v-model="loginForm.username"
            placeholder="请输入用户名"
            prefix-icon="User"
            clearable
          />
        </el-form-item>

        <el-form-item prop="password">
          <el-input
            v-model="loginForm.password"
            type="password"
            placeholder="请输入密码"
            prefix-icon="Lock"
            show-password
            clearable
            @keyup.enter="handleLogin"
          />
        </el-form-item>

        <el-form-item>
          <el-button
            type="primary"
            :loading="loading"
            class="login-btn"
            @click="handleLogin"
          >
            登 录
          </el-button>
        </el-form-item>

        <el-form-item>
          <el-button class="reset-btn" @click="handleReset">
            重 置
          </el-button>
        </el-form-item>
      </el-form>

      <div class="login-tip">
        <p>提示：用户名和密码长度至少3位即可登录</p>
      </div>
    </div>
  </div>
</template>

<style scoped>
.login-container {
  height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
}

.login-card {
  width: 420px;
  padding: 40px;
  background: #fff;
  border-radius: 8px;
  box-shadow: 0 4px 20px rgba(0, 0, 0, 0.15);
}

.login-title {
  text-align: center;
  font-size: 28px;
  color: #303133;
  margin-bottom: 8px;
}

.login-subtitle {
  text-align: center;
  font-size: 14px;
  color: #909399;
  margin-bottom: 30px;
}

.login-form {
  margin-top: 10px;
}

.login-btn {
  width: 100%;
}

.reset-btn {
  width: 100%;
}

.login-tip {
  text-align: center;
  margin-top: 20px;
  padding-top: 20px;
  border-top: 1px solid #eee;
}

.login-tip p {
  font-size: 12px;
  color: #c0c4cc;
}
</style>
