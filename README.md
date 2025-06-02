# 电梯眩晕问题探究 (Elevator-Issues)
v0.1.0

开源协议：GPL-3.0

提示：代码粘贴需点击窗口左上角“Powershell”图标，在“Edit/编辑”中选择“Paste/粘贴”。**不可使用 `Ctrl+V` 快捷键！**  
复制：选中后按 `Enter`；  
粘贴：左上角菜单 编辑>粘贴；  
终止：`Ctrl+C`。

## 原始数据要求
csv 格式。第一列时间，单位 $s$。第四列竖直方向加速度，单位 $m\cdot s^{-2}$。

样例使用 Physics Toolbox Suite Pro 采集。

## 使用步骤
### 安装 WSL 并 Clone 到本地
1. `Win+X, I` 打开 Poweshell。
2. `wsl --update`
3. `wsl --install Ubuntu-24.04`，设置账户、密码，进入 WSL。
4. `git clone https://gitee.com/taoran-01/Elevator-Issues.git ~/Repo/Elevator-Issues/`
5. `cd ~/Repo/Elevator-Issues/`
<!-- 6. `git checkout dev` -->
### 环境配置
`sudo ./scripts/setup.sh`，输入密码确认。  
必须全部 `SUCCESS`。若有 `FAILED`，重试。
### 执行
`sudo ./scripts/main.sh 数据`，输入密码确认。  
电梯上行样例 `./data/up_01.csv`  
电梯下行样例 `./data/dn_01.csv`
### 结果查看
文件资源管理器，上方地址栏输入：
`\\wsl.localhost\Ubuntu-24.04\home\origami\Repo\Elevator-Issues\result`
全选，复制到本地，查看。
### 清理（不必要）
`sudo ./scripts/clear.sh`，输入密码确认。检查后输入 `y`。
### 退出并卸载 WSL
1. `sudo poweroff`，输入密码确认。
2. `wsl --unregister Ubuntu-24.04`

## 结果文件说明
- acc 加速度
- vel 速度
- dsp 位移
- corr 浮动修正（末速度=0）
- filt 低通滤波（截止频率 3Hz，先滤波后修正）

向下为正方向。

## 其他
FFT/IFFT 使用 [FFTW3](https://www.fftw.org/fftw3.pdf)

`C/C++ Extension` 需要在 WSL 中单独安装。
