<?php

/**
 * @file
 * Administrative page callbacks for the update_jira module.
 */

/**
 * Form constructor for the admin settings form.
 *
 * @see update_jira_menu()
 * @ingroup forms
 */
function update_jira_admin_settings_form($form_state) {
  $states = update_jira_default_states();

  $form = array();

  $form['update_jira_project_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Project key'),
    '#default_value' => variable_get('update_jira_project_key', ''),
    '#description' => t('The Jira project to track updates.'),
  );

  foreach ($states as $state => $default) {
    $form[constant($state)] = array(
      '#type' => 'fieldset',
      '#title' => t('Settings for !description', array('!description' => $default['description'])),
      '#collapsible' => TRUE,
      '#collapsed' => !variable_get('update_jira_create_ticket:' . constant($state), $default['create_ticket']),
    );

    $form[constant($state)]['update_jira_create_ticket:' . constant($state)] = array(
      '#type' => 'checkbox',
      '#title' => t('Create tickets'),
      '#default_value' => variable_get('update_jira_create_ticket:' . constant($state), $default['create_ticket']),
    );

    $form[constant($state)]['update_jira_issuetype:' . constant($state)] = array(
      '#type' => 'textfield',
      '#title' => t('Issue type'),
      '#default_value' => variable_get('update_jira_issuetype:' . constant($state), $default['issuetype']),
    );

    $form[constant($state)]['update_jira_priority:' . constant($state)] = array(
      '#type' => 'textfield',
      '#title' => t('Priority'),
      '#default_value' => variable_get('update_jira_priority:' . constant($state), $default['priority']),
    );

    $form[constant($state)]['update_jira_issue_summary:' . constant($state)] = array(
      '#type' => 'textfield',
      '#title' => t('Issue summary'),
      '#default_value' => variable_get('update_jira_issue_summary:' . constant($state), $default['issue_summary']),
    );

    $form[constant($state)]['update_jira_issue_description:' . constant($state)] = array(
      '#type' => 'textarea',
      '#title' => t('Issue description'),
      '#default_value' => variable_get('update_jira_issue_description:' . constant($state), $default['issue_description']),
    );
    $form[constant($state)]['tokens'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('update'),
      '#global_types' => TRUE,
      '#click_insert' => TRUE,
    );
  }

  $form['update_jira_ignored_projects'] = array(
    '#type' => 'textarea',
    '#title' => 'Ignore projects',
    '#default_value' => variable_get('update_jira_ignored_projects', ''),
  );

  return system_settings_form($form);
}

/**
 * Validate the update_jira form values.
 *
 * While an empty project key is valid we should warn the user that this
 * disables the global functionality.
 */
function update_jira_admin_settings_form_validate($form, &$form_state) {
  $form_values = $form_state['values'];
  if (empty($form_values['update_jira_project_key'])) {
    drupal_set_message(t("You didn't define a Project key."), 'warning');
  }
}
