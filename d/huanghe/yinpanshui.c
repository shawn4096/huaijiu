// by XiaoYao

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "Ӫ��ˮ");
	set("long", @LONG
�����ǵ��������޳���ʱפ���ĵط��������ξ��з�����������
�Դ�����פ�����˺ü�����ˮ����ʹʿ���ǲ��ú��ֿ���ɬ����ˮ��
�����˵صİ����ǽ�����ΪӪ��ˮ��������ľ�Ϊ�����񾮡���
LONG );
	set("exits", ([
		"southwest" : __DIR__"bingcao",
		"northeast" : __DIR__"guchangcheng",
	]));
	set("no_clean_up", 0);
	set("outdoors", "�ƺ�");
	set("coor/x",90);
  set("coor/y",160);
   set("coor/z",0);
   setup();
}

