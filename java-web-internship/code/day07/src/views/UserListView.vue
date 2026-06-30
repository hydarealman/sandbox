<script>
import { useUserStore } from '@/stores/user'

export default {
  name: 'UserListView',
  data() {
    return {
      searchKeyword: '',
      dialogVisible: false,
      dialogTitle: '',
      isEdit: false,
      userForm: {
        id: null,
        name: '',
        age: null,
        email: '',
        phone: '',
        department: '',
      },
      formRules: {
        name: [
          { required: true, message: '请输入姓名', trigger: 'blur' },
          { min: 2, message: '姓名至少2个字符', trigger: 'blur' },
        ],
        age: [
          { required: true, message: '请输入年龄', trigger: 'blur' },
        ],
        email: [
          { required: true, message: '请输入邮箱', trigger: 'blur' },
          { type: 'email', message: '请输入正确的邮箱格式', trigger: 'blur' },
        ],
        phone: [
          { required: true, message: '请输入手机号', trigger: 'blur' },
        ],
        department: [
          { required: true, message: '请选择部门', trigger: 'change' },
        ],
      },
      departments: ['技术部', '产品部', '设计部', '市场部', '财务部', '人事部'],
      currentPage: 1,
      pageSize: 5,
    }
  },
  computed: {
    userStore() {
      return useUserStore()
    },
    filteredUsers() {
      return this.userStore.searchUsers(this.searchKeyword)
    },
    pagedUsers() {
      const start = (this.currentPage - 1) * this.pageSize
      return this.filteredUsers.slice(start, start + this.pageSize)
    },
    total() {
      return this.filteredUsers.length
    },
  },
  methods: {
    handleSearch() {
      this.currentPage = 1
    },
    handleReset() {
      this.searchKeyword = ''
      this.currentPage = 1
    },
    handleAdd() {
      this.dialogTitle = '添加用户'
      this.isEdit = false
      this.userForm = {
        id: null,
        name: '',
        age: null,
        email: '',
        phone: '',
        department: '',
      }
      this.dialogVisible = true
    },
    handleEdit(row) {
      this.dialogTitle = '编辑用户'
      this.isEdit = true
      this.userForm = { ...row }
      this.dialogVisible = true
    },
    handleDelete(row) {
      this.$confirm('确定要删除该用户吗？', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning',
      }).then(() => {
        this.userStore.deleteUser(row.id)
        this.$message.success('删除成功')
      }).catch(() => {
        // 取消删除
      })
    },
    handleSubmit() {
      this.$refs.userFormRef.validate((valid) => {
        if (valid) {
          if (this.isEdit) {
            this.userStore.updateUser(this.userForm)
            this.$message.success('修改成功')
          } else {
            this.userStore.addUser({ ...this.userForm })
            this.$message.success('添加成功')
          }
          this.dialogVisible = false
        }
      })
    },
    handleDialogClose() {
      this.$refs.userFormRef.resetFields()
    },
    handlePageChange(page) {
      this.currentPage = page
    },
    handleSizeChange(size) {
      this.pageSize = size
      this.currentPage = 1
    },
  },
}
</script>

<template>
  <div class="user-list-container">
    <!-- 搜索栏 -->
    <el-card class="search-card">
      <el-row :gutter="15" class="search-row">
        <el-col :span="8">
          <el-input
            v-model="searchKeyword"
            placeholder="搜索姓名、邮箱、部门..."
            clearable
            @keyup.enter="handleSearch"
            @clear="handleReset"
          >
            <template #prefix>
              <span>🔍</span>
            </template>
          </el-input>
        </el-col>
        <el-col :span="8">
          <el-button type="primary" @click="handleSearch">搜索</el-button>
          <el-button @click="handleReset">重置</el-button>
        </el-col>
        <el-col :span="8" class="text-right">
          <el-button type="success" @click="handleAdd">+ 添加用户</el-button>
        </el-col>
      </el-row>
    </el-card>

    <!-- 用户表格 -->
    <el-card class="table-card">
      <el-table
        :data="pagedUsers"
        border
        stripe
        style="width: 100%"
        empty-text="暂无数据"
      >
        <el-table-column type="index" label="序号" width="60" align="center" />
        <el-table-column prop="name" label="姓名" width="120" align="center" />
        <el-table-column prop="age" label="年龄" width="80" align="center" />
        <el-table-column prop="email" label="邮箱" min-width="180" />
        <el-table-column prop="phone" label="手机号" width="150" align="center" />
        <el-table-column prop="department" label="部门" width="120" align="center" />
        <el-table-column label="操作" width="180" align="center" fixed="right">
          <template #default="{ row }">
            <el-button type="primary" size="small" @click="handleEdit(row)">
              编辑
            </el-button>
            <el-button type="danger" size="small" @click="handleDelete(row)">
              删除
            </el-button>
          </template>
        </el-table-column>
      </el-table>

      <!-- 分页 -->
      <div class="pagination">
        <el-pagination
          v-model:current-page="currentPage"
          v-model:page-size="pageSize"
          :page-sizes="[5, 10, 15, 20]"
          :total="total"
          layout="total, sizes, prev, pager, next, jumper"
          background
          @size-change="handleSizeChange"
          @current-change="handlePageChange"
        />
      </div>
    </el-card>

    <!-- 添加/编辑对话框 -->
    <el-dialog
      v-model="dialogVisible"
      :title="dialogTitle"
      width="500px"
      :close-on-click-modal="false"
      @close="handleDialogClose"
    >
      <el-form
        ref="userFormRef"
        :model="userForm"
        :rules="formRules"
        label-width="80px"
        size="default"
      >
        <el-form-item label="姓名" prop="name">
          <el-input v-model="userForm.name" placeholder="请输入姓名" />
        </el-form-item>
        <el-form-item label="年龄" prop="age">
          <el-input-number
            v-model="userForm.age"
            :min="1"
            :max="150"
            placeholder="请输入年龄"
            style="width: 100%"
          />
        </el-form-item>
        <el-form-item label="邮箱" prop="email">
          <el-input v-model="userForm.email" placeholder="请输入邮箱" />
        </el-form-item>
        <el-form-item label="手机号" prop="phone">
          <el-input v-model="userForm.phone" placeholder="请输入手机号" />
        </el-form-item>
        <el-form-item label="部门" prop="department">
          <el-select
            v-model="userForm.department"
            placeholder="请选择部门"
            style="width: 100%"
          >
            <el-option
              v-for="dept in departments"
              :key="dept"
              :label="dept"
              :value="dept"
            />
          </el-select>
        </el-form-item>
      </el-form>
      <template #footer>
        <el-button @click="dialogVisible = false">取消</el-button>
        <el-button type="primary" @click="handleSubmit">确定</el-button>
      </template>
    </el-dialog>
  </div>
</template>

<style scoped>
.user-list-container {
  max-width: 1200px;
  margin: 0 auto;
}

.search-card {
  margin-bottom: 20px;
}

.text-right {
  text-align: right;
}

.table-card {
  margin-bottom: 20px;
}

.pagination {
  margin-top: 20px;
  display: flex;
  justify-content: flex-end;
}
</style>
