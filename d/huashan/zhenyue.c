// Room: /d/huashan/zhenyue.c
// Date: Look 99/03/25

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���������Ϊƽ̹���ϡ���ɽ���οͶ��ڴ�������Ϣ�ټ���ǰ�С�������
�����ª�����磬���Ƕ�����ճ��ߣ�����ͷ��ЪϢ�ڴˡ�
LONG
        );
        set("exits", ([ 
	  "northup" : __DIR__"canglong",
	  "eastup" : __DIR__"chaoyang",
	  "southup" : __DIR__"yunu",
]));
        set("outdoors", "��ɽ" );

        set("coor/x",70);
  set("coor/y",40);
   set("coor/z",50);
   setup();
}
