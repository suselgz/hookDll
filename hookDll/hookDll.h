// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� HOOKDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// HOOKDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef HOOKDLL_EXPORTS
#define HOOKDLL_API __declspec(dllexport)
#else
#define HOOKDLL_API __declspec(dllimport)
#endif

// �����Ǵ� hookDll.dll ������
class HOOKDLL_API ChookDll {
public:
	ChookDll(void);
	// TODO:  �ڴ�������ķ�����
};

extern HOOKDLL_API int nhookDll;

HOOKDLL_API int fnhookDll(void);

extern "C" HOOKDLL_API void SetMouseHookAll(HWND hwnd);
extern "C" HOOKDLL_API void SetKeyBoarHookAll(HWND hwnd);
extern "C" HOOKDLL_API void UnMouseHookAll();
extern "C" HOOKDLL_API void UnKeyBoarHook();
