inherit ROOM;
#include <ansi.h>
void create()
{
        set("short",HIC"����ͤ"NOR);
        set("long", @LONG
����ͤ�����ݵı�����ϲ࣬��Ϊ����������ţ�ʹ����Ů���ٶ�ϲ��
��������ͥɢ������ͤ�з�����ȥ������һƬ���̵Ĳ�ƺ��ͤ����Ȼ���ʴ�
֮�У���������������ƿƣ������ܿ����ܣ�ͤ�ϵĶ��Һ�ʯ���ϵ����(lian)
ʹ�˸���ϲ�����
LONG
);
set("outdoors", "suzhou");
        set("item_desc", ([
        "lian" :     "������±��޼� ��ˮԶɽ������\n"
        
]));
        set("exits", ([ 
"north" : __DIR__"beidajie1",
	"southeast" : __DIR__"dongdajie3",
        "south" : __DIR__"baodaiqiao",
 "southwest" : __DIR__"xidajie1",
        ]));
        set("coor/x",110);
  set("coor/y",-220);
   set("coor/z",0);
   setup();
}
