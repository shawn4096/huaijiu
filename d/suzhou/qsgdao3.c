inherit ROOM;

void create()
{
        set("short", "��ʯ�ٵ�");
        set("long",@long
������һ����ʯ����ϣ����������Ե÷ǳ���æ����ʱ������������Ҵ�
���������������һЩС��̯���ƺ���һ�����С�����ͨ�����ݳǡ�
long);
	set("outdoors", "suzhou");
	set("exits",([
		"east" : __DIR__"westgate",
           "west" : __DIR__"qsgdao5",
	]));
	set("coor/x",70);
  set("coor/y",-210);
   set("coor/z",0);
   setup();
}
