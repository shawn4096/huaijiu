// by xiaoyao

inherit ROOM;

void create()
{
	set("short", "渡船");
	set("long", @LONG
黄河上的小舟都是这种很简陋的小舟。一位中年艄公正站在船尾
吃力地掌舵，一位膀子壮硕的小伙子也在船头用劲地划水撑船。黄河
水流湍急，船下滑很快，横渡却很慢。
LONG );
	set("no_clean_up", 0);
	set("outdoors", "黄河");
	setup();
}

