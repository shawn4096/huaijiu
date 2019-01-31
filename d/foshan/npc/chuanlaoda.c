// laoda.c

#include <ansi.h>
inherit NPC;

int ask_mwd();

void create()
{
	set_name("船老大", ({ "chuan laoda" }) );
	set("gender", "男性" );
	set("age", 42);
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("rank_info/respect", "船老大");
	set("inquiry", ([
		"name": "我就是这里的老大，他们都叫我小马哥。",
		"rumors": "听说不久前有一只船对被倭寇给抢了，船上的财宝都让他们给藏到一个小岛上了。",
		"here": "这里是附近唯一的出海渡口了。",
		"马五德": (: ask_mwd :),

	]) );
	setup();
}

int ask_mwd()
{
        object ob, me, hc, *thing;
        int i; 
        me=this_player();
        ob = load_object("/clone/npc/zhong-shentong");

	if( me->query("id") == ob->query("winner") ) {
             command("say 呦，中神通大驾亲至，有失远迎。\n");
             return 1;
        }

        if( me->query_condition("killer") && !wiz_level(me) ) {
             command("say 你个通缉犯打听马老爷子是什么意思？\n");
             return 1;
        }

        if (!me->query_temp("marks/勇闯夺命岛2")) {
             command("say 马老爷子的大名我们自然听说过，不过客官想问什么呢？\n");
             return 1;
        }

        thing = deep_inventory(me);
	i = sizeof(thing);
	while (i--)
	     if (thing[i]->is_character()) {
		   message_vision("船老大把手一拦，道：你还想带个人上船？\n", me);
	           command("knock "+(string)me->query("id"));
		   command("say 你慢慢发呆吧！\n");
		   me->add_busy(100 + random(200));
	           return 1;
		} 

       
             
        if(!objectp(hc=find_object(__DIR__"hc1"))) hc=load_object(__DIR__"hc1");
	     
        if(hc->query_temp("curstatus",1)=="run") {
		   if(!objectp(hc=find_object(__DIR__"hc2"))) hc=load_object(__DIR__"hc2");

		   if(hc->query_temp("curstatus",1)=="run") {
			 if(!objectp(hc=find_object(__DIR__"hc3"))) hc=load_object(__DIR__"hc3");
			 if(hc->query_temp("curstatus",1)=="run")
							
                               return notify_fail("船老大两手一摊，道：客官来的真不巧，船只有些破损正在修理，您过会再来吧。\n");
                   }
             }

	say("船老大瞪大了眼睛，吃惊地说：客官就是马老爷子请来的高人？失敬失敬！\n您老这是艺高人胆大啊，废话就不说了，请上船。\n" );
	message_vision(CYN"只见一艘快船已经驶进渡口，$N慢慢走了进去。\n" NOR,me);	
        me->move(hc);
        me->set("dmd_enter_time",time());
        me->apply_condition("dmd_time",90);
        me->delete_temp("dmd/done");
	hc->set_temp("curstatus","run");
        CHANNEL_D->do_channel( this_object(), "rumor",
                sprintf("%s开始勇闯夺命岛的冒险了！", me->name(1)));
	return 1;
}

void kill_ob(object ob)
{
	ob->remove_killer(this_object());
	remove_killer(ob);
	message_vision("船老大喝问$N：“在我的地盘你也敢撒野？！”\n", ob);
	message_vision("$N连忙赔笑道：“不敢，不敢。”\n", ob);
}
