// yuchuan5.c ؤ���洬

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","�洬");
	set("long", @LONG
ͻȻ����ǰһ������������һ�Ҵ��ϣ��װ������ż�����ؤ��һ����׽
ʭ�ӣ� һ���þ����˫�۲�ͣ�ش������㡣������һ�����ţ�����ں����ģ�
��ʲôҲ�Ʋ�����
LONG
	);
	set("exits",([
	"enter" : __DIR__"fenduo1",
	"west"  : __DIR__"yugang"
	]));
	set("coor/x",130);
  set("coor/y",-470);
   set("coor/z",10);
   setup();
}

