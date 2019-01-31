 // by Xiaoyao

inherit NPC;
#include <ansi.h>
void destroying(object, object);
int ask_skills();

void create()
{
        set_name("丁典", ({ "ding dian", "ding" }));
        set("long", "这人满脸虬髯，头发长长的直垂至颈，衣衫破烂不堪，简直如同荒山中的野人。\n");
        set("gender", "男性");
        set("age", 35);
        set("unique", 1);

        set_skill("cuff", 120);
        set_skill("dodge", 120);
        set_skill("parry", 130);
        set_skill("qingmang-jian", 120);
        set_skill("taizu-quan", 150);
        set_skill("shenzhao-jing", 120);
        map_skill("dodge","qingmang-jian");
        map_skill("force","shenzhao-jing");
        map_skill("parry", "qingmang-jian");
        map_skill("cuff","taizu-quan");
        prepare_skill("cuff","taizu-quan");
        set("max_neili",3000);
        set("neili",3000);
        set("max_qi",1680);
        set("qi",1680);
        set("eff_jingli",1800);
        set("jingli",1800);
        set("jiali",100);
        set("inquiry", ([
		"狄云" : "我也不知道狄兄弟现在在哪里！也许吉人天相，但愿无碍！",
		"name": "你问这干嘛，我就是丁典，你有什么事情？",
		"here": "这里便是苏州监狱，嘿嘿。",
		"神照经" : (: ask_skills :),
		"苏州" : "这里便是苏州。",
		"连城诀" : "你问这个干什么？哼......",
		"连城剑法" : "你问这个干什么？哼......",
		"万震山" : "梅念笙老先生收的三个不肖弟子啊，怎么有这样的江湖败类。",
		"言达平" : "梅念笙老先生收的三个不肖弟子啊，怎么有这样的江湖败类。",
		"戚长发" : "梅念笙老先生收的三个不肖弟子啊，怎么有这样的江湖败类。",
		"梅念笙" : "铁骨墨萼梅念笙老先生，可惜死得冤枉啊。",
		"菊友" : "她是霜华的贴身丫鬟。",
		"凌退思" : "他就是霜华的爹爹，真是苍天弄人啊。",
		"凌霜华" : "她就是翰林府大小姐，也是我最心爱的人。",
	])); 
        set("combat_exp", 600000);
        set("shen_type", 1);
        setup();
        carry_object("/clone/armor/cloth")->wear();

}

int accept_object(object me, object obj)
{
        object key;
        me = this_player();
        if ((string)obj->query("id")=="lu juhua") {
        message("vision",me->name()+"给丁典一盆绿菊花。\n",environment(me),
            ({me}));
        key = unew("/clone/armor/wucanyi");
        if(!clonep(key)) return notify_fail (CYN"丁典说道：我已经托人给霜华捎话了，不劳您大驾了。\n"NOR);  
        if(clonep(key) && key->violate_unique()){
           destruct(key);
           return notify_fail (CYN"丁典说道：我已经托人给霜华捎话了，不劳您大驾了。\n"NOR);
           } 
        command("touch "+me->query("id"));
        command("say 这位"+RANK_D->query_respect(me)+"是霜华派你来捎话的吧,嗨！我们可是苦命的鸳鸯。");
        key->move(me);        
        message_vision("$n递给$N一件乌蚕衣。\n", me, this_object() );
        command("say 这位"+RANK_D->query_respect(me)+"真是太感谢你了,这件宝衣你拿去用吧。");
        if(!me->query("szj") && !me->query_temp("szj")) me->set_temp("szj",1);
        remove_call_out("destroying");
        call_out("destroying", 1, this_object(), obj);
        return 1;
        }
        return 0;
}

void destroying(object me,object obj)
{
        destruct(obj);
        return;
}

int ask_skills() 
{
	object me = this_player();
	int i;
        if(me->query("szj"))
        {
                 if(me->query("potential") > 4)
		 {
                        message_vision("$N向$n请教有关神照经的奥妙。\n", me, this_object());
			me->receive_damage("jing", 10);
			tell_object(me,HIY"你听了丁典的指点，对神照经的奥妙似乎有些心得。\n"NOR);
			me->add("potential",-(random(3)+1));
			if(me->query("potential") < 0) me->set("potential",0);
			if(me->query_skill("shenzhao-jing") >= 220) me->improve_skill("shenzhao-jing", 25+me->query_int()*2);
			
			else
			{    me->improve_skill("shenzhao-jing", 25+random(me->query_int()));
			     me->improve_skill("force", random(me->query_int())/2);
			  }
                      }
                 else 
		{
			message_vision("$N向$n请教有关神照经的奥妙。\n", me, this_object());
			tell_object(me,HIY"你听了丁典的指点，可是还是不能理解。\n"NOR);
		}
		return 1;
	}

        if(!me->query_temp("szj") && !me->query("szj")) 
                {
                        command("say 你问这个干嘛。神照经是铁骨墨萼梅念笙老先生曾经教我的一套内功的秘经。");
                        return 1;
                        }

        if(me->query_temp("szj") && !me->query("szj")) 
                {
                        if(me->query("szj_fail") >= 3)
                        {
                                command("say 已经多次传授，这位"+RANK_D->query_respect(me) +"怎么都还没有领悟！");
                                return 1;
                          }
                        if(me->query("szj_exp") && me->query("combat_exp")-me->query("szj_exp")<50000)
                        {
                                command("say 以"+RANK_D->query_respect(me) +"当前的经验恐怕还是难以领悟，还是抓紧去练功去吧。");
                                return 1;
                          }
        me->set("szj_exp",me->query("combat_exp")); 
	i= random(15);
	if(i==1)
	   {
		   command("say 这是铁骨墨萼梅念笙老先生曾经教我的一套内功的秘经。我就传授给"+RANK_D->query_respect(me) +"吧。");
		   command("say 不过功效嘛......");		   
		   command("hehe "+me->query("id"));
		   tell_object(me,HIY"你听了丁典的指点，对神照经的奥妙似乎有些心得。\n\n"NOR);
		   me->improve_skill("shenzhao-jing", 5+random(me->query_int()));
		   me->improve_skill("force", random(me->query_int())/2);
		   me->set("szj",1);
		   log_file("quest/szj", sprintf("%s(%s) 失败%d次学到神照经绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("szj_fail"),i,me->query("combat_exp")) );
	   }
	   else
	   {
		   command("say 这是铁骨墨萼梅念笙老先生曾经教我的一套内功的秘经。我就传授给"+RANK_D->query_respect(me) +"吧。");
		   command("say 如果你留心，当年在武馆之内就刻有神照经内功心法。嘿嘿。");
		   command("ah "+me->query("id"));
		   tell_object(me,HIY"你听了丁典的指点，可是对神照经的奥妙全然不得要领。\n\n"NOR);
		   command("sigh "+me->query("id"));
		   me->add("szj_fail",1);
		   command("courage");   		   
		   log_file("quest/szj", sprintf("%s(%s) 学习神照经失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("szj_fail"),i,me->query("combat_exp")) );
	   }
	  } 
	 return 1;
}