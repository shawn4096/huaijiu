// yubang.c �������

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","�����ͷ");
	set("long", @LONG
���Ǹ��ݵ�һ����ۣ�����ͣ�����洬������������Ŵ󵣴󵣵�����
�ţ�������㻹���ʱĻ�������Զ�����м�����ؤ���ڴ��ߣ������������
�µ������ڿ�ԣ��㲻�ɵ��е���ġ������ӣ��Ǽ����л������ϻ���������
����������Ī�ǡ��������Ǿ���ؤ��ģ�
LONG
	);
	set("exits", ([
	"enter" : __DIR__"yuchuan1",
	"west" :  "/d/fuzhou/haigang", 
        ]));
	set("outdoors","����");
        set("coor/x",120);
  set("coor/y",-470);
   set("coor/z",0);
   setup();
}
