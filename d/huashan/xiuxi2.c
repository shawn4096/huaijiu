// Room: /d/huashan/xiuxi2.c
// Date: Look 99/03/25

inherit ROOM;

void create()
{
        set("short", "����Ϣ��");
        set("long", @LONG
���Ǽ�������᷿�����Ŵ������ţ����ߺܻ谵������������ֻ����
�����һ����ʰ����������Ĵ󴲣����ž�������˯����
LONG
        );

        set("sleep_room", 1);
        set("no_fight", 1);

        set("exits",([
        	"north" : __DIR__"celang4",
	]));

        set("indoors", "��ɽ" );
        set("coor/x",90);
  set("coor/y",-40);
   set("coor/z",80);
   setup();
}
