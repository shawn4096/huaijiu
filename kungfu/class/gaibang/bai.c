// bai.c 白世镜
// By Looklove@SJ 2000/9/27
// Looklove modified 2001.5.25 肚饿中

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_dao();
object ppl;
int ask_rumors(object);


void create()
{
        set_name("白世镜", ({ "bai shijing", "bai"}));
        set("title", "丐帮执法长老");
        set("gender", "男性");
        set("age", 47);
        set("long", "这人是丐帮中的执法长老，向来铁面无私。\n"
        	    "帮中大小人等，纵然并不违犯帮规刑条，见到他也是惧怕三分。\n");
        set("attitude", "peaceful");
        set("unique", 1);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("apprentice",1);
        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 1600);
        set("max_jing", 1600);
        set("neili", 3400);
        set("max_neili", 3400);
        set("jiali", 100);

        set("combat_exp", 1500000);

        set_skill("force", 150); 		// 基本内功
        set_skill("huntian-qigong", 150); 	// 混天气功
        set_skill("dodge", 150); 		// 基本轻功
        set_skill("xiaoyaoyou", 150); 		// 千里行乞
        set_skill("parry", 150); 		// 基本招架
        set_skill("strike", 150);
        set_skill("lianhua-zhang",150);
        set_skill("begging", 90);
        map_skill("force", "huntian-qigong");
        map_skill("parry","lianhua-zhang");
        map_skill("strike","lianhua-zhang");
        map_skill("dodge", "xiaoyaoyou");
        prepare_skill("strike", "lianhua-zhang");

        create_family("丐帮", 18, "九袋长老");

        set("inquiry", ([
                "丐帮" : "我们丐帮是天下第一大帮！\n",
                "乔峰" : "乔帮主是个好汉。\n",
                "萧峰" : "他不就是乔峰，我们的前任帮主。\n",
	        "法刀" : (: ask_dao :),
	        "rumors" : (: ask_rumors :),
        ]));
        setup();
        carry_object("/kungfu/class/gaibang/obj/bainayi")->wear();
        carry_object("/kungfu/class/gaibang/obj/gb_budai9")->wear();
}
void attempt_apprentice(object ob)
{
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "丐帮") {
                command("say 你还是去别的门派看看吧。");
                return;
        }
        if ((int)ob->query("gb_bags") >= 2
        && ob->query("family/family_name") != "丐帮" ) {
                command("say 丐帮可容不下你这种背信弃义的小人！");
                command("kill "+ob->query("id"));
                return;
        }
        if ((int)ob->query("gb_bags") < 3
        || ob->query("gb_job") < 300 ){
                command("say 你在帮中的资历尚浅，过些日子再说吧！");
                return;
        }
        if (ob->query("shen")< ob->query("combat_exp")/2) {
                command("say 想入我刑堂，再多做侠义的事吧。");
                return;
        }
        command("say 好吧，希望" + RANK_D->query_respect(ob) +
        "能好好学习本门武功，将来在江湖中闯出一番作为。");
        command("recruit " + ob->query("id"));
        ob->set("title",sprintf("丐帮刑堂%s袋弟子",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","刑堂");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}
string ask_dao()
{
        object me;
        object *list;

        me = this_player();

        if ( me->query("family/family_name") != "丐帮")
                return RANK_D->query_respect(me) +
                "非我丐帮好汉，不知此话从何谈起？";

        if ( me->query("family/master_name")!="白世镜")
                return RANK_D->query_respect(me) +
                "不是我刑堂弟子，何出此言？";

        if ( me->query_temp("fadao/asked"))
        	return "刚才你不是问过了么？";

        if ( present("fa dao", me))
                return RANK_D->query_respect(me) +
                "法刀你不是拿着呢吗？";

        list = filter_array(objects(), (: $1->query("id")=="fa dao":));
        if ( sizeof(list) > 8) {
        	me->set_temp("fadao/asked",1);
        	return "其他兄弟正在执法，等会吧";
        }

        new("/clone/weapon/blade/fadao")->move(me);
	me->set_temp("fadao/asked",1);
        message_vision("$N得到一柄法刀。\n",me);
        return "好，你代我去各地巡视，发现不守帮规的弟子，就地处置。";
}

int ask_rumors(object me)
{
    	int exp;
    	object where, target, *list;

    	me = this_player();
    	if(!me) return 0;

    	me->add_temp("count",1);
    	exp = me->query("combat_exp");

	if((string)me->query("family/family_name")!="丐帮"){
		command("en "+me->query("id")+"");
		return 1;
	}
	if((string)me->query("family/master_name")!="洪七公"){
		command("pat "+me->query("id")+"");
		return 1;
	}
    	if (query("waiting")) {
        	command("say 你等等吧，我在等人呢。");
        	return 1;
        }
	if(me->query_temp("h7g/k_target")||!me->query_temp("h7g/quest")){
		return 1;
	}
    	if (me->query_temp("count") > 3) {
        	me->delete_temp("count");
        	command("say 你还是一会再来吧。\n");
        	return 1;
        }

    	ppl = me;
    	list = filter_array(users(), (:
    				    $1->query("combat_exp")>ppl->query("combat_exp")*3/4
    				 && $1->query("combat_exp")<ppl->query("combat_exp")*5/4
    				 && !wizardp($1)
    				 && interactive($1)
    				 && query_idle($1)<120
    				 && $1->query("PKS")>50
    				 && objectp(environment($1))
    				 && !$1->query_temp("pigging_seat")
    				 && $1->query("family")
   				 && !$1->query_condition("relax")
    				 && !$1->query_condition("wuguan_job")
                                 && $1->query("family/family_name")!="丐帮"
                                 && $1->query("family/family_name")!="少林派"
                                 && $1->query("family/family_name")!="武当派"
                                :));
    	list -= ({me,0});

    	if(sizeof(list)<random(10)+1){
        command("say 我这里现在没什么事，你过会再来吧。\n");
        return 1;
	}
    	target = list[random(sizeof(list))];
    	where = environment(target);
       	command("say 听说"+HIR+target->query("name")+HIW+"("+target->query("id")+")"+CYN"最近作恶多端，你去替我把他宰了！");
       	command("say 你去"+HIG+where->query("short")+CYN+"附近找找看。");
       	target->set_temp("no_zhong",1);
       	target->set_temp("h7g/k_target",1);
       	set("target",target->query("name"));
       	set("targetid",target->query("id"));
       	me->set_temp("h7g/k_target",1);
       	set("waiting",1);
       	return 1;
}



int accept_object(object me, object ob)
{
	int amount;
	object n_money;

	amount = random(100)+100;
    	if (!me->query_temp("h7g/k_target")) {
       		command("say 给我这个做什么？");
       		return 0;
       	}
    	if (ob->query("name")==query("target")+"的首级"
        && ob->query("victim_id")==query("targetid")
        && ob->query("material")=="meat") {
       		command("nod");
       		if (random(2)!=1) {
       			command("say 好，这是给你的奖励。另外，帮主传话来，让你去一趟。");
       			me->set_temp("h7g/xlz_jobv",1);
                	n_money = new("/clone/money/gold");
                	n_money->set_amount(50);
                	n_money->move(me);
       		}
       		else {
       		command("say 好，做的好，这是给你的奖励。");
                n_money = new("/clone/money/gold");
                n_money->set_amount(amount);
                n_money->move(me);
		}
       		set("waiting",0);
       		return 1;
       	}
       	else{
       	command("say 给我这个做什么？");
       	return 0;
       	}
}