import matplotlib.pyplot as plt
# 导入中文显示库函数
from matplotlib.font_manager import FontProperties
font_set = FontProperties(fname=r"c:\windows\fonts\simsun.ttc", size=15)
x_values=[1,2,2,3,3,4,5,6]
y_values=[3,2,7,9,5,6,5,8]
plt.scatter(x_values,y_values,s=50)
# 图表名称
plt.title('散点图',fontproperties=font_set)
# 设置x轴名称
plt.xlabel("weight")
# 设置y轴名称
plt.ylabel("value")
plt.show()
