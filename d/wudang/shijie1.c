// /d/wudang/shijie1.c ʯ��
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
������һ����ʵ��ʯ���ϣ���ʱ�������˻����ʹ��������߹���
һ�������£�һ�����ͱڣ�̧ͷ��Լ�ɼ�ɽ���Ƶ������壬ɽ����棬
���������������Ŀ�������
LONG
        );
        set("exits", ([
                "southup" : __DIR__"shijie2",
                "northdown" :__DIR__"xuanyuemen",
        ]));

        set("objects",([
                __DIR__"npc/shusheng" : 1,

        ]));
        
        set("coor/x",20);
  set("coor/y",20);
   set("coor/z",10);
   setup();

}
