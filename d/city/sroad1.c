inherit ROOM;

void create()
{
        set("short", "��ʯ�ٵ�");
        set("long",@long
������һ����ʯ����ϣ����������ǳ���æ����ʱ����������ҴҶ�����
�����ǳ������ν��뺣�ڵĵط���������ͨ�����ճǡ�
long);
	set("outdoors", "suzhou");
	set("exits",([
        "southeast" : "/d/suzhou/qsgdao6",
		"north" : __DIR__"jiangnan",
	]));
	set("coor/x",100);
  set("coor/y",-170);
   set("coor/z",0);
   setup();
}
