#pragma once

// ��������
enum stage
{
	stage_init = 0,
	stage_import_ova,
	stage_start_machine,
	stage_connect_to_input,
	stage_sub_window,
	stage_vm_booting,
};

// �������̴�����
enum error_code
{
	error_null = 0,
	error_import_ova_failed,
	error_start_machine_failed,
	error_init_ogl_render_failed,
	error_sub_window_failed,
	error_vm_booting_timeout,
};

// �����Ϣ����
enum mouse_event_type
{
	met_unknown = -1,
	met_lbutton_press = 0,
	met_lbutton_release,
	met_wheel_up,
	met_wheel_down,
};

// �������Ȼص�
using StartProcCallback = std::function<void(stage, error_code, int)>;

// �����ں˸���ճ���ص�
using ReceiveCopyPasteCallback = std::function<void(char*)>;
