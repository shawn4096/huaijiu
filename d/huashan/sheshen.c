// Room: /d/huashan/sheshen.c
// Date: Look 99/03/25

inherit ROOM;

void create()
{
        set("short", "������");
	 set("long", @LONG
����һ�μ�խ���յ�ɽ�£�����������ƣ�����Ԩ���޵ס��粻С�ģ�һ
ʧ�����ȥ��ֻ������ͷ���Ҳ�����
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
	  "eastdown" : __DIR__"canglong",
	 ]));
	
	 set("no_die", 1);
        set("no_clean_up", 0);
        set("outdoors", "��ɽ" );

        set("coor/x",60);
  set("coor/y",50);
   set("coor/z",70);
   setup();
}
