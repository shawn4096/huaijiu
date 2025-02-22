// Room: /d/city/lichunyuan.c
// Verified By Numa @Sj 00-05-28
// Modified By Numa@SJ 00-09-16

#include <ansi.h>
#define HERE "/d/city/lichunyuan"
#define THERE "/d/city/xidajie3.c"
#define MAO "/d/city/dongxiangfang.c"
#define this_quest_is_open "yes"

inherit ROOM;

void create()
{
	set("short", "丽春院");
	set("long", @LONG
这便是扬州城鸣玉坊四大院子之一丽春院。华灯初上，院子中一片丝竹和
欢笑之声，中间又夹杂着猜枚行令，唱曲闹酒，当真是笙歌处处，一片升平景
象。老板娘便是当朝大红人鹿鼎公的老娘韦春芳, 她正“咯咯”笑个不停。
LONG
	);

	set("exits", ([
                "east" : __DIR__"dongxiangfang",
                "west" : __DIR__"xixiangfang",
		"south" : __DIR__"mingyufang",
	]));

	set("objects", ([
		__DIR__"npc/xiaosong" : 1,
		__DIR__"npc/wei" : 1,
                __DIR__"npc/yanxiao2" : 1,
                __DIR__"npc/yanxiao" : 1,
        	__DIR__"npc/guinu" : 1,
	        __DIR__"npc/yanshang" : 2,
	]));

	set("coor/x",100);
        set("coor/y",20);
        set("coor/z",0);
        setup();
}

void init()
{
	object me = this_player();
	
    if (this_quest_is_open == "yes"
        && userp(me)
        && !me->query("mao18/pass")
        && me->query_temp("mao18/jg_pass")
        && me->query("age") <=20
        && random(me->query_int()) > 20
        && random(me->query_kar()) > 22) {
                remove_call_out("do_happen1");
		call_out("do_happen1",10,me);
        }
}

int do_happen1(object me)
{
	if (base_name(environment(me)) != HERE)
		return 1;
	tell_object(me,HIY"
    忽然之间，坊南坊北同时有五六人齐声吆喝：“各家院子生意上的朋友，姑娘们，来

花银玩儿的朋友们，大伙儿听着：我们来找一个人，跟旁人并不相干，谁都不许乱叫乱动。

不听吩咐的，可别怪我们不客气！”一阵吆喝之后，鸣玉坊中立即静了片刻，跟着各处院

子中喧声四起，女子惊呼声，男子叫囔声，乱成一团。\n"NOR);
    if (random(me->query_con()) > 14) {
		message_vision(HIR"\n$N咳了几声，把肩耸了耸，向里屋望去。\n"NOR,me);
        remove_call_out("do_happen2");
        call_out("do_happen2",4,me);
		return 1;
	}
	message_vision(HIR"\n$N突然全身发抖，吓的飞也似的逃了出去。\n"NOR,me);
	me->move(THERE);
	tell_room(environment(me),HIG + me->name(1) + "突然口中狂呼：“杀人啦！！”，从丽春院奔了出来！\n"NOR);
	return 1;
}

int do_happen2(object me)
{
	if (base_name(environment(me)) != HERE)
		return 1;
	tell_object(me,HIW"
    砰的一声，大门撞开，涌进十七八名短装结束，白布包头，青带缠腰的大汉。

    盐枭中有一个五十余岁的老者抱拳自左至右，又自右至左的拱了拱手，跟着朗声道：“

天地会姓贾的朋友。贾老六贾老兄，在不在这里？”\n"NOR);
        if (random(me->query_kar()) > 18) {
		tell_object(me,HIR"
    忽然东边厢房中有个粗豪的声音说道：“是谁在这里大呼小叫，打扰老子寻快活？”\n"NOR);
        remove_call_out("do_happen3");
        call_out("do_happen3",4,me);
		return 1;
	}
    tell_object(me,HIY"\n你见到只是两拨人打架，没甚意思，就自顾自走了。\n"NOR);
	me->move(THERE);
	tell_room(environment(me),HIG + me->name(1) + "贼头贼脑的从丽春院走了过来！\n"NOR);
	return 1;
}

int do_happen3(object me)
{
	if (base_name(environment(me)) != HERE)
		return 1;
	tell_object(me,HIC"
    那老者走上几步，向内张去，朦胧中见一名虬髯大汉坐在床上，头上包了白布，脸上

并无刀疤，果然不是贾老六。那老者大声问道：“阁下好身手，请问尊姓大名？”

    房内那人骂道：“你爹爹姓什么叫什么，老子自然姓什么叫什么。好小子，连你爷爷

的姓名也忘记了。”\n"NOR);
	if (present("wei chunfang",environment(me))) {
		tell_object(me,HIR"
    站在一旁的众妓女之中，突然有个三十来岁的中年妓女“咯咯”一声，笑了出来。一

名私盐贩子抢上一步，拍拍两记耳光，打得那妓女眼泪鼻涕齐流。那盐枭骂道：“他妈的

臭婊子，有什么好笑？”那妓女吓得不敢再说。\n"NOR);
        remove_call_out("do_happen4");
        call_out("do_happen4",4,me);
		return 1;
	}
	tell_object(me,"你等了半天也不见有啥动静，就自顾自走了。\n");
	me->move(THERE);
	tell_room(environment(me),HIG + me->name(1) + "贼头贼脑的从丽春院走了过来！\n"NOR);
	return 1;
}

int do_happen4(object me)
{
	if (base_name(environment(me)) != HERE)
		return 1;
	tell_object(me,HIY"
    你看的兀自生气，就冲上前去向着那个盐枭踢了一脚，刚好踢中那人的阴囊。

    那盐枭右拳举起，又往你头顶击落。你向前一冲，无地可避，便即推开厢房房门，

奔了进去。\n"NOR);
	me->move(MAO);
	if (present("mao shiba",environment(me))) {
		tell_object(me,HIR"
    只见那髯须大汉三下五除二就解决了房内的盐枭。众盐枭一声喊，抬起地下伤者，

纷纷夺门而去。
    
    那髯须大汉呼呼喘气，隔了一会伸手撑起身子，似是又碰到了痛处，大哼了一声。

你过去扶起他，那人道：“拾起刀，递给我！”你拾起地下单刀，递入他右手。\n"NOR);
        call_out("do_happen5",3,me);
		return 1;
	}
	tell_object(me,"你见里面也没什么人，就赶紧钻出窗户逃走了。\n");
	me->move(THERE);
	tell_room(environment(me),HIG + me->name(1) + "贼头贼脑的从丽春院走了过来！\n"NOR);
	return 1;
}

int do_happen5(object me)
{
	tell_object(me,HIY"
    那髯须大汉说道：“看不出你这小朋友还满够义气。好，现下我要赶去城西得胜山

和别人比武，你如果愿意前去，就跟我一起走。("RED"yes"HIY"|"RED"no"HIY")\n"NOR);
	me->set_temp("mao18/passed1",1);
	return 1;
}

/*
int do_yes()
{
	object me = this_player();
	object ob;
	
	if (!me->query_temp("mao18/passed1"))
		return 0;
	if (!(ob = present("mao shiba",environment(me))))
		return notify_fail("茅十八都早走了！！\n");
	tell_object(me,HIW"
    你立马说道：“干么不去？好朋友有福同享，有难同当。”

    那人哈哈大笑，说道：“这两句话说得好。老子在江湖上听人说过了几千遍，有福共

享的家伙见得多了，有难同当的人却碰不到几个。咱们走罢！”\n"NOR);
	call_out("do_go",1,me);
	return 1;
}

int do_no()
{
	object me = this_player();
    object ob;
	
	if (!me->query_temp("mao18/passed1"))
		return 0;
	if (!(ob = present("mao shiba",environment(me))))
		return notify_fail("茅十八都早走了！！\n");
	tell_object(me,HIW"
    你战抖的答道：“小人家中。。。家中还有些事，请大爷您就放过小的我吧！”

    那人哈哈大笑，说道：“看你这小家伙也没什么骨气，赶快滚吧！”\n"NOR);
	me->delete_temp("mao18/passed1");
	return 1;
}
	
*/
