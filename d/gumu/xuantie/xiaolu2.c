// by dubei
// Modify By River@sj 99.5.24
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
       set("short",YEL"ɽ·"NOR);
       set("long", @LONG
����һ����᫵�ɽ·��·���ϼ�����һЩ��ɳ����ϥ��Ұ�ݼ�����·����
���ˣ���������Ұ��Ʈ�������㡣���ܲ�ʱ����һ�����Ұ�޽���, ͷ����
һЩ��֪����С����������ȥ��
LONG
    );
       set("outdoors", "����");

       set("exits", ([
           "northup" : __DIR__"xiaolu3",
           "southdown" : __DIR__"xiaolu1",
       ]));

       setup();
}
