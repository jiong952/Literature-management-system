本人大二的数据结构课设，使用的数据结构是B树

# 基本需求

题目：文献管理系统

【问题描述】

设计一个文献管理系统，使用B树结构实现对文献的入库、清除库存、借阅和归还等操作。

【基本要求】

(1) 文献登记的内容至少包括文献号、文献名、著者、现存量和总库存量等五项。

(2) 文献信息可使用文件存储，也可只在内存存储。文献号作为关键字，使用3阶B树对文献号建立索引。

(3) 系统实现的操作及其功能定义如下： 

①入库：新购入的文献，确认文献号之后登记到系统。如果这种文献在系统中已有，则只将总库存量增加。 

②清除：某种文献已无保留价值，将它从系统中注销。

③借阅：如果一种文献的现存量大于零，则借出一本，登记借阅者的证件和归还期限。 

④归还：注销对借阅者的登记，改变该文献的现存量。 

⑤显示：以凹入表的形式显示B树。 

【扩展要求】

(1) 将程序一次运行的操作记入日志文件中。

(2) 增加列出某著者全部文献名操作

(3) 增加列出某种文献状态的操作。状态信息除了包括这种文献记录的全部信息外，还包括最早到期的借阅者证件。

(4) 增加预约借阅文献功能

(5) 使用4阶以上B树重新实现文献管理系统

# 功能实现

a)  **插入文献**:将要增添的书的书号、书名、作者名、入库数添加入文献管理系统中。如果这种文献在系统中已存在，则只将总库存量增加，每增加一个书号则以凹入表的形式显示 B 树形状。

b)  **删除文献**：某种书已无保留价值，将它的全部信息删除，每清除一个书号则以凹入表的形式显示 B 树形状。

c)  **借阅文献**：如果一种书的现存量大于零，则借出一本，登记借阅者的姓名和图书证

d)  号。如果无现存量，则进行预约，登记预约者的姓名和图书证号。

e)  **归还文献**：注销对借阅者的登记，改变该书的现存量。当该书有预约者时，将归还的图书给到预约者，可根据归还时间判断是否按时归还。

f)  **查看全部文献**：用表格输出所有文献的信息。

g)  **查看某文献信息**：查看指定某一本书的全部信息。管理员可查看文献的借阅状态

h)  **查看某文献借阅者信息**：用表格输出某本书的全部借阅者信息。

i)  **以凹入表的形式显示 B** **树**。

**j)**  **按照作者名查看该作者的全部文献**

k)  **文件读取**，将运行的图书数据保存到BookData.txt中，每次运行先进行初始化操作，每次退出系统进行保存操作

l)  **日志管理**，将一次运行的操作保存到日志文件中当天时间_LOG_RECORD.log

# 使用说明

编程环境：DecC++

编程语言：C++

程序入口：文献管理系统.exe

管理员密码：123456