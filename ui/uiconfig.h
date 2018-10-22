
#ifndef _UICONFIG_H_
#define _UICONFIG_H_

#define WINDOW_TITLE "星光凯明六自由度平台"

#define IDC_BTN_START_SHOW_TEXT "运行"

#define IDC_BTN_SINGLE_UP_SHOW_TEXT    "单缸上"
#define IDC_BTN_SINGLE_DOWN_SHOW_TEXT  "单缸下"

#define IDC_BTN_CONNECT_SHOW_TEXT      "所有缸上"
#define IDC_BTN_DISCONNECT_SHOW_TEXT   "所有缸下"

#define IDC_STATIC_POSE_SHOW_TEXT      "姿态"
#define IDC_STATIC_LENGTH_SHOW_TEXT    "缸长"
#define IDC_STATIC_SENSOR_SHOW_TEXT    "传感器"

#define IDC_STATIC_X_VAL_SHOW_TEXT     "纵向幅值"
#define IDC_STATIC_Y_VAL_SHOW_TEXT     "横向幅值"
#define IDC_STATIC_Z_VAL_SHOW_TEXT     "垂向幅值"
#define IDC_STATIC_ROLL_VAL_SHOW_TEXT  "侧倾角度"
#define IDC_STATIC_PITCH_VAL_SHOW_TEXT "俯仰角度"
#define IDC_STATIC_YAW_VAL_SHOW_TEXT   "航向角度"

#define IDC_STATIC_X_HZ_SHOW_TEXT      "纵向频率"
#define IDC_STATIC_Y_HZ_SHOW_TEXT      "横向频率"
#define IDC_STATIC_Z_HZ_SHOW_TEXT      "垂向频率"
#define IDC_STATIC_ROLL_HZ_SHOW_TEXT   "侧倾频率"
#define IDC_STATIC_PITCH_HZ_SHOW_TEXT  "俯仰频率"
#define IDC_STATIC_YAW_HZ_SHOW_TEXT    "航向频率"

#define IDC_STATIC_X_PHASE_SHOW_TEXT      "纵向相位"
#define IDC_STATIC_Y_PHASE_SHOW_TEXT      "横向相位"
#define IDC_STATIC_Z_PHASE_SHOW_TEXT      "垂向相位"
#define IDC_STATIC_ROLL_PHASE_SHOW_TEXT   "侧倾相位"
#define IDC_STATIC_PITCH_PHASE_SHOW_TEXT  "俯仰相位"
#define IDC_STATIC_YAW_PHASE_SHOW_TEXT    "航向相位"

#define IDC_STATIC_TEST_SHOW_TEXT      "测试(位移单位:1mm, 角度单位:1°, 频率单位:1Hz, 相位单位:1°)"
#define IDC_BUTTON_TEST_SHOW_TEXT      "运行测试"

#define CORPORATION_NAME "北京市星光凯明动感仿真模拟器中心"

#define APP_TITLE "大型特种车驾驶模拟训练系统"
#define APP_TITLE_FONT_SIZE 240

#define CHART_TITLE "位姿信息"
#define CHART_LEFT_AXIS_TITLE "数值单位(mm, °)"
#define CHART_BOTTOM_AXIS_TITLE "时间(t/s)"

#define INIT_FAIL_MESSAGE "初始化电机运动控制卡失败，检查连线！"
#define NOT_FIND_MOTION_MESSAGE "错误：找不到伺服电机!"

#define STATUS_INIT_ING "正在初始化"
#define STATUS_INIT_FINISH "初始化完成"
#define STATUS_INIT_FAIL "初始化失败"

#define SIXDOF_NOT_BOTTOM_MESSAGE "所有缸不在底部"
#define SIXDOF_NOT_BOTTOM_AND_RISE_MESSAGE "所有缸不在底部，禁止上升"
#define SIXDOF_NOT_MIDDLE_MESSAGE "缸没有处于静止，不能回中"
#define SIXDOF_NOT_BEGIN_MESSAGE "缸没有处于静止，不能开始"

#endif
