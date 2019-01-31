#include <ansi.h>
inherit F_MASTER;
inherit NPC;

string ask_emjiuyin();

void create()
{
       set_name("风陵师太", ({
               "fengling shitai",
               "fengling",
               "shitai",
       }));
       set("long","她就是峨嵋派第二代掌门人风陵师太了。\n"
	"她面目慈祥，便如寻常老尼一般，浑不带一丝尘俗之气。\n"
       );

       set("gender", "女性");
       set("attitude", "friendly");
       set("unique", 1);
       set("per", 30);
       set("class", "bonze");
       set("age", 80);
       set("shen", 20000);
       set("str", 26);
       set("int", 30);
       set("con", 29);
       set("dex", 30);
       set("max_qi", 6700);
       set("max_jing", 6000);
       set("eff_jingli", 3500);
       set("neili", 15000);
       set("max_neili", 14000);
       set("jiali", 100);
       set("combat_exp", 2800000);
        

       set_skill("dacheng-fofa", 200);
       set_skill("linji-zhuang", 200);
       set_skill("jieshou-jiushi", 280);
       set_skill("huifeng-jian", 280);
       set_skill("sixiang-zhang", 280);
       set_skill("yanxing-daofa", 280);
       set_skill("hand", 280);
       set_skill("literate", 150);
       set_skill("strike", 280);
        set_skill("linji-jianzhen", 200);
       set_skill("sword", 280);
       set_skill("blade", 280);
       set_skill("parry", 280);
       set_skill("dodge", 280);
       set_skill("force", 200);
       set_skill("anying-fuxiang", 280);
       
       map_skill("force", "linji-zhuang");
       map_skill("sword", "huifeng-jian");
       map_skill("blade", "yanxing-daofa");
       map_skill("parry", "jieshou-jiushi");
       map_skill("dodge", "anying-fuxiang");
       map_skill("strike", "sixiang-zhang");
       map_skill("hand", "jieshou-jiushi");
       prepare_skill("hand", "jieshou-jiushi");

       set("inquiry", 
                ([
			"融合" : (: ask_emjiuyin :),

]));

       set("chat_chance_combat", 40);
       set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
                (: perform_action, "sword.liaoyuan" :),
                (: perform_action, "hand.foguang" :)
        }));
       create_family("峨嵋派", 2, "前掌门");

       setup();
       set_temp("apply/armor", 60);
       set_temp("apply/damage", 40);
       set_temp("apply/attack", 50);
       set_temp("apply/dodge", 40);
       if(random(2)==1)
       		carry_object(BINGQI_D("gangjian"))->wield();
       UPDATE_D->get_cloth(this_object());
}
void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }       
     
}
void greeting(object me)
{
        int shen;
        if(!me) return;
        shen = me->query("shen");
        if(shen <= -200000 && me->query("family/family_name") == "峨嵋派"){
        	command("chat* smash "+me->query("id"));
        	command("say 你满眼瘴气，身带邪气，从今天起你不再是峨嵋弟子了！");
        	command("expell " + me->query("id"));
	}
	if(shen <0 && shen > -200000 && me->query("family/family_name") == "峨嵋派"){
		command("look "+me->query("id"));
		command("say 我看你满眼瘴气，身带邪气，最近是不是在外面做了什么坏事？");
	}
	else command("say 阿弥陀佛。");
}
int accept_object(object me, object ob)
{

	if( me->query("family/family_name") == "峨嵋派"
	&& ob->query("id") == "zhi huan" && me->query_temp("marks/pass_yitian")) {
		if(!(me->query_temp("marks/get_ring"))) {
			command("say 这枚指环是从何而来？哼，想骗老尼，没那么容易！");
			command("consider " + me->query("id"));
			command("say 拿命来吧！");
			kill_ob(me);
			return 1;
		}
		command("say 好吧，既然把掌门指环交给了我，你就有资格做老尼的衣钵传人了。\n");
		me->delete_temp("marks/pass_yitian");
		me->delete_temp("marks/get_ring");
		me->set_temp("bai_feng",1); 
		remove_call_out("destroying");
		call_out("destroying", 1, me, ob);
		return 1;
	}

	if( me->query("family/family_name") == "峨嵋派"	&& ob->query("id") == "yu zhuo" ) {
		if(!(me->query_temp("marks/拿"))) {
			command("say 这支黑玉镯是从何而来？哼，想骗老尼，没那么容易！");
			command("consider " + me->query("id"));
			command("say 拿命来吧！");
			kill_ob(me);
			return 1;
		}
		command("say 好吧，既然把黑玉镯交给了我，那我就将融合之道传授于你。\n");
		me->delete_temp("marks/拿");
		tell_object(me, HIY "你在风陵师太的教导下，成功将九阴之秘融合于临济十二庄「日月」字决之中。\n" NOR);
		me->set("emjiuyin",1); 
		remove_call_out("destroying");
		call_out("destroying", 1, me, ob);
		return 1;
	} 
	return 0;
}
void attempt_apprentice(object ob)
{
        object me; 
        mapping ob_fam, my_fam;
        string name, new_name;

        me = this_object();
        my_fam  = me->query("family");
        name = ob->query("name");
        if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "峨嵋派")
        {
                command("say " + RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
        }
        if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "峨嵋派") 
        {
                command("say " + RANK_D->query_respect(ob) + "是俗家弟子，不能拜在老尼门下学艺。");
                return;
        }

        if ( !ob->query_temp("bai_feng"))
        {
         command("say " + RANK_D->query_respect(ob) + "，你没有拿到掌门指环，不能拜老尼为师。");
         return;
        }       
        if ( ob_fam["generation"] == (my_fam["generation"] + 1)) 
        {
         command("say 徒儿，你功夫练的如何了?\n");
         ob->delete_temp("bai_feng");
         return;
         } 
        if ( ob_fam["generation"] == (my_fam["generation"] + 2) )
        {
           if ( ob->query_temp("bai_feng") )
           {
                ob->delete_temp("bai_feng");
                command("chat 老尼垂死之年，终得到一个衣钵传人，真是可喜可贺 !");
                name = ob->query("name");
                new_name = "灭" + name[2..3];
                ob->set("name", new_name);
                command("say 从今以后你的法名叫做" + new_name + "，恭喜你成为灭字辈长老之一 !");
                command("recruit " + ob->query("id"));
                return;
                }
            command("say 你没有找来指环，我不能把衣钵传你。\n");  
            return;
         }
          command("say 你班辈不合，不可越级拜师。\n");
          return;
        }  

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

string ask_emjiuyin()
{
	mapping fam;
        int skill;
        skill = this_player()->query_skill("jiuyin-zhengong", 1);
 
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "峨嵋派")
		return RANK_D->query_respect(this_player()) + 
		"与本派素无来往，不知此话从何谈起？";
	if ( skill < 120 )
		return RANK_D->query_respect(this_player()) + 
		"你的九阴真功太差，无法融合。";
	if ( present("yu zhuo", this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"既已取得黑玉镯，为何不将其交于老尼？";

	return "你没有拿到黑玉镯，老尼不能为你解答融合的问题。";

}