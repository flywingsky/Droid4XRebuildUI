#pragma once

// 启动过程
enum stage
{
	stage_init = 0,
	stage_import_ova,
	stage_start_machine,
	stage_connect_to_input,
	stage_sub_window,
	stage_vm_booting,
};

// 启动过程错误码
enum error_code
{
	error_null = 0,
	error_import_ova_failed,
	error_start_machine_failed,
	error_init_ogl_render_failed,
	error_sub_window_failed,
	error_vm_booting_timeout,
};

// 鼠标消息类型
enum mouse_event_type
{
	met_unknown = -1,
	met_lbutton_press = 0,
	met_lbutton_release,
	met_wheel_up,
	met_wheel_down,
};

// 启动进度回调
using StartProcCallback = std::function<void(stage, error_code, int)>;

// 接收内核复制粘贴回调
using ReceiveCopyPasteCallback = std::function<void(char*)>;
