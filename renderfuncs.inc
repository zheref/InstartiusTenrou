<?php
/**
 * @author Instartius Corporation
 * @package Tenrou
 * @version 0.0.1
 * @change 13/01/19/10:58:XX -> Process Code Behind cuando Render hook before
 */

/**
 * Renderiza el archivo con el nombre especificado (sin la extension php)
 * Se asume extension php. Si se requiere cargar otro tipo de archivo, usar
 * la funcion _r para renderizar archivos con extension especificada
 * @param $nombre El nombre del archivo sin extension (se asume .php)
 */
function render($nombre)
{
    process_code_behind($nombre);
    include(TEMPLATEPATH . '/components/' . $nombre . '.php');
}

/**
 * Renderiza el archivo con el nombre y extension especificados
 * Se asume el formato tipico de nomenclatura de archivo.extension.
 * @param $nombre El nombre del archivo con extension
 */
function _r($nombre)
{
    include(TEMPLATEPATH . '/components/' . $nombre);
}

/**
 * Renderiza el componente que normalmente se encarga de inicializar
 * Los tags primeros y primordiales del HTML, como lo es la etiqueta
 * de apertura del HTML, los namespace (en caso de XHTML), el doctype
 * y OPCIONALMENTE cargar el HEAD ahi mismo.
 * Archivo -> begin.php
 */
function begin_html()
{
    process_code_behind('begin');
    render('begin');
}

/**
 * Renderiza el componente que normalmente se encarga de finalizar
 * y cerrar todos los tags de ambito mas global (cercanos al document HTML)
 * Archivo -> end.php
 */
function end_html()
{
    process_code_behind('end');
    render('end');
}

/**
 * Renderiza el componente HTML que se encarga exclusivamente de
 * las etiquetas méticas del HEAD como lo son los metadatos, el titulo,
 * los recursos, los estilos, las varibles de entorno cliente, los scripts,
 * las bases, entre otros posibles elementos.
 * @param null $slug El slug alternativo
 */
function ins_head($slug = null)
{
    if(!is_null($slug))
        render('head' . '-' . $slug);
    else
        render('head');
}

/**
 * Renderiza el componente visual HTML responsable de la cabecera de la pagina
 * PUEDE contener el logo, algunos navs y algunos widgetbars
 * @param null $slug El slug alternativo
 */
function ins_header($slug = null)
{
    if(!is_null($slug))
        render('header' . '-' . $slug);
    else
        render('header');
}

/**
 * Renderiza el componente visual HTML responsable del logo del proyecto,
 * empresa o producto. Puede incluir un nav a nivel de DropDown
 * @param null $slug El slug alternativo
 */
function ins_logo($slug = null)
{
    if(!is_null($slug))
        render('logo' . '-' . $slug);
    else
        render('logo');
}

/**
 * Renderiza el componente visual HTML responsable de los navs de la pagina
 * PUEDEN contener mas de un nav
 * @param null $slug El slug alternativo
 */
function ins_nav($slug = null)
{
    if(!is_null($slug))
        render('nav' . '-' . $slug);
    else
        render('nav');
}

function ins_comment_form()
{
    $fields = array
    (
        'author' => '<div class="input-control text"><input required="required" name="author" type="text" placeholder="Nombre" /><button class="helper"></button></div>',
        'email' => '<div class="input-control text"><input required="required" name="email" type="email" placeholder="E-mail" /><button class="helper"></button></div>',
        'url' => '<div class="input-control text"><input name="url" type="url" placeholder="Blog (opcional)" /><button class="helper"></button></div>',
    );
    $fieldsfilter = apply_filters('comment_form_default_fields', $fields);
    $args = array
    (
        'fields' => $fieldsfilter,
        'title_reply' => 'Comentarios Tradicionales (Wordpress)',
        'logged_in_as' => '<p>Autentificado como <a href="' . admin_url('profile.php') . '">' . wp_get_current_user()->get('first_name') . '</a>. <a class="button" style="float: right" href="' . wp_logout_url(get_permalink()) . '"><i class="icon-exit"></i>Cerrar sesión</a></p>',
        'label_submit' => 'Publicar comentario!',
        'cancel_reply_link' => 'Abortar comentarios!',
        'comment_field' => '<div class="input-control textarea"><textarea required="required" name="comment" placeholder="Su comentario. Puede incluir ciertas etiquetas HTML." class="commenttextarea" style="width: 100%"></textarea></div>',
        'comment_notes_before' => '<p><small>Los campos que no dicen (opcional) son obligatorios. Tu e-mail no sera publicado.</small></p>',
        'comment_notes_after' => ''
    );
    comment_form($args);
}

function ins_comment_loop($comment, $args, $depth)
{
    $GLOBALS['comment'] = $comment;
    $GLOBALS['depth'] = $depth;
    $GLOBALS['args'] = $args;
    render('commentsloop');
}



?>