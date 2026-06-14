$ErrorActionPreference = "Stop"

$mysql = "C:\Program Files\MySQL\MySQL Server 8.0\bin\mysql.exe"
$root = Split-Path -Parent $PSScriptRoot
$sqlDir = Join-Path $root "sql"
$outDir = Join-Path $root "outputs"
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

$env:MYSQL_PWD = "123456"

$scripts = @(
  "01_orderdb_setup_and_programming.sql",
  "02_orderdb_queries.sql",
  "03_bookdb_definition_indexes_views_updates.sql",
  "04_orderdb_procedures_triggers.sql",
  "05_security_mysql.sql",
  "06_bookdb_integrity.sql",
  "07_execution_plan.sql",
  "08_transactions.sql"
)

try {
  foreach ($script in $scripts) {
    $path = Join-Path $sqlDir $script
    $output = Join-Path $outDir ([IO.Path]::GetFileNameWithoutExtension($script) + ".txt")
    Write-Host "Running $script ..."
    & $mysql -uroot --default-character-set=utf8mb4 --table --execute="source $($path.Replace('\','/'))" > $output 2>&1
    if ($LASTEXITCODE -ne 0) {
      Get-Content -LiteralPath $output -Tail 80
      throw "MySQL script failed: $script"
    }
  }

  Write-Host "Running transaction isolation demo ..."
  python (Join-Path $PSScriptRoot "run_transaction_isolation_demo.py")
  if ($LASTEXITCODE -ne 0) {
    throw "Isolation demo failed"
  }
} finally {
  Remove-Item Env:MYSQL_PWD -ErrorAction SilentlyContinue
}

Write-Host "All database experiments finished."
